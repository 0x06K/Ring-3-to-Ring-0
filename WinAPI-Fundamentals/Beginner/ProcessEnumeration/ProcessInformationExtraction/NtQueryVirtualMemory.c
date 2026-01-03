#include <windows.h>
#include <winternl.h>
#include <stdio.h>

#pragma comment(lib, "ntdll.lib")


#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)
#define STATUS_ACCESS_DENIED ((NTSTATUS)0xC0000022L)


typedef enum _MEMORY_INFORMATION_CLASS {
    MemoryBasicInformation,           // 0
    MemoryWorkingSetInformation,      // 1
    MemoryMappedFilenameInformation,  // 2
    MemoryRegionInformation,          // 3
    MemoryWorkingSetExInformation,    // 4
    MemorySharedCommitInformation,    // 5
    MemoryImageInformation,           // 6
    MemoryRegionInformationEx,        // 7
    MemoryPrivilegedBasicInformation, // 8
    MemoryEnclaveImageInformation     // 9
} MEMORY_INFORMATION_CLASS;

typedef NTSTATUS (NTAPI *pNtQueryVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID BaseAddress,
    MEMORY_INFORMATION_CLASS MemoryInformationClass,
    PVOID MemoryInformation,
    SIZE_T MemoryInformationLength,
    PSIZE_T ReturnLength
);

int main() {
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    if (!ntdll) return 1;

    pNtQueryVirtualMemory NtQueryVirtualMemory =
        (pNtQueryVirtualMemory)GetProcAddress(ntdll, "NtQueryVirtualMemory");

    if (!NtQueryVirtualMemory) {
        printf("NtQueryVirtualMemory not found\n");
        return 1;
    }

    MEMORY_BASIC_INFORMATION mbi;
    PVOID address = 0;

    printf("BaseAddress        Size        State     Protect\n");
    printf("----------------------------------------------------\n");

    while (NtQueryVirtualMemory(
        GetCurrentProcess(),
        address,
        MemoryBasicInformation,
        &mbi,
        sizeof(mbi),
        NULL
    ) == STATUS_SUCCESS)
    {
        printf("%p  %8zu  0x%08X  0x%08X\n",
            mbi.BaseAddress,
            mbi.RegionSize,
            mbi.State,
            mbi.Protect
        );

        address = (PBYTE)mbi.BaseAddress + mbi.RegionSize;
    }

    return 0;
}
