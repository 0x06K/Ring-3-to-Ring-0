#include <windows.h>
#include <winternl.h>
#include <stdio.h>

// Function pointer typedef for NtGetNextProcess
typedef NTSTATUS (NTAPI *pNtGetNextProcess)(
    HANDLE ProcessHandle,
    ACCESS_MASK DesiredAccess,
    ULONG HandleAttributes,
    ULONG Flags,
    PHANDLE NewProcessHandle
);

// Function pointer for NtQueryInformationProcess
typedef NTSTATUS (NTAPI *pNtQueryInformationProcess)(
    HANDLE ProcessHandle,
    PROCESSINFOCLASS ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PULONG ReturnLength
);

// Extended PROCESS_BASIC_INFORMATION
typedef struct _PROCESS_BASIC_INFORMATION_EXT {
    NTSTATUS ExitStatus;
    PVOID PebBaseAddress;
    ULONG_PTR AffinityMask;
    LONG BasePriority;
    ULONG_PTR UniqueProcessId;
    ULONG_PTR InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION_EXT;

#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#define STATUS_NO_MORE_ENTRIES ((NTSTATUS)0x8000001AL)

int main() {
    printf("[+] Process Enumeration using NtGetNextProcess\n");
    printf("[+] ================================================\n\n");

    // Load ntdll.dll
    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
    if (!hNtdll) {
        printf("[-] Failed to load ntdll.dll\n");
        return 1;
    }

    // Get function pointers
    pNtGetNextProcess NtGetNextProcess = 
        (pNtGetNextProcess)GetProcAddress(hNtdll, "NtGetNextProcess");
    
    pNtQueryInformationProcess NtQueryInformationProcess = 
        (pNtQueryInformationProcess)GetProcAddress(hNtdll, "NtQueryInformationProcess");

    if (!NtGetNextProcess) {
        printf("[-] NtGetNextProcess not available (requires Windows 10+)\n");
        printf("[-] Your Windows version doesn't support this API\n");
        return 1;
    }

    if (!NtQueryInformationProcess) {
        printf("[-] NtQueryInformationProcess not available\n");
        return 1;
    }

    printf("%-10s %-50s\n", "PID", "Process Name");
    printf("================================================================\n");

    HANDLE hCurrentProcess = NULL;
    NTSTATUS status;
    int processCount = 0;

    // Iterate through all processes
    while (TRUE) {
        HANDLE hNextProcess = NULL;
        
        // Get the next process handle
        status = NtGetNextProcess(
            hCurrentProcess,                      // Current process handle (NULL for first)
            PROCESS_QUERY_LIMITED_INFORMATION,    // Access rights
            0,                                    // Handle attributes
            0,                                    // Flags (reserved, must be 0)
            &hNextProcess                         // Receives next process handle
        );

        // Close the previous handle
        if (hCurrentProcess != NULL) {
            CloseHandle(hCurrentProcess);
            hCurrentProcess = NULL;
        }

        // Check if enumeration is complete
        if (status == STATUS_NO_MORE_ENTRIES) {
            break; // No more processes
        }

        if (status != STATUS_SUCCESS) {
            printf("[-] NtGetNextProcess failed with NTSTATUS: 0x%08X\n", status);
            break;
        }

        // Update current process handle
        hCurrentProcess = hNextProcess;

        // ============================================================
        // Now we have a HANDLE, but we need to query for actual info
        // ============================================================

        // Get Process ID using NtQueryInformationProcess
        PROCESS_BASIC_INFORMATION_EXT pbi = {0};
        ULONG returnLength = 0;

        status = NtQueryInformationProcess(
            hCurrentProcess,
            ProcessBasicInformation,
            &pbi,
            sizeof(pbi),
            &returnLength
        );

        DWORD pid = 0;
        if (status == STATUS_SUCCESS) {
            pid = (DWORD)pbi.UniqueProcessId;
        } else {
            // Fallback to GetProcessId
            pid = GetProcessId(hCurrentProcess);
        }

        // Get Process Name using QueryFullProcessImageName
        char processName[MAX_PATH] = {0};
        DWORD size = sizeof(processName);

        if (QueryFullProcessImageNameA(hCurrentProcess, 0, processName, &size)) {
            // Extract just the filename from full path
            char* filename = strrchr(processName, '\\');
            if (filename) {
                filename++; // Move past the backslash
                printf("%-10lu %-50s\n", pid, filename);
            } else {
                printf("%-10lu %-50s\n", pid, processName);
            }
        } else {
            // Access denied or other error
            printf("%-10lu %-50s\n", pid, "<Access Denied>");
        }

        processCount++;
    }

    // Clean up last handle if any
    if (hCurrentProcess != NULL) {
        CloseHandle(hCurrentProcess);
    }

    printf("\n[+] Total processes enumerated: %d\n", processCount);
    printf("[+] Done!\n");

    return 0;
}