#include <windows.h>
#include <winternl.h>
#include <stdio.h>

#pragma comment(lib, "ntdll.lib")

typedef NTSTATUS (NTAPI* pNtQueryInformationProcess)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);

int main() {
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    if (!ntdll) return 1;

    pNtQueryInformationProcess NtQueryInformationProcess =
        (pNtQueryInformationProcess)GetProcAddress(ntdll, "NtQueryInformationProcess");

    if (!NtQueryInformationProcess) {
        printf("Failed to resolve NtQueryInformationProcess\n");
        return 1;
    }

    // Open current process
    HANDLE hProcess = GetCurrentProcess();

    // Query basic information
    PROCESS_BASIC_INFORMATION pbi;
    ULONG retLen;
    NTSTATUS status = NtQueryInformationProcess(
        hProcess,
        ProcessBasicInformation,
        &pbi,
        sizeof(pbi),
        &retLen
    );

    if (!NT_SUCCESS(status)) {
        printf("NtQueryInformationProcess failed: 0x%X\n", status);
        return 1;
    }

    printf("Current PID: %lu\n", GetCurrentProcessId());
    printf("Parent PID: %lu\n", (ULONG)(ULONG_PTR)pbi.InheritedFromUniqueProcessId);
    printf("PEB Base Address: %p\n", pbi.PebBaseAddress);

    // Optional: read PEB to get command line
    PEB peb;
    if (ReadProcessMemory(hProcess, pbi.PebBaseAddress, &peb, sizeof(peb), NULL)) {
        UNICODE_STRING cmdLine;
        RTL_USER_PROCESS_PARAMETERS upp;
        if (ReadProcessMemory(hProcess, peb.ProcessParameters, &upp, sizeof(upp), NULL)) {
            cmdLine = upp.CommandLine;
            WCHAR* buffer = (WCHAR*)malloc(cmdLine.Length + 2);
            if (ReadProcessMemory(hProcess, cmdLine.Buffer, buffer, cmdLine.Length, NULL)) {
                buffer[cmdLine.Length / sizeof(WCHAR)] = 0;
                wprintf(L"Command Line: %s\n", buffer);
            }
            free(buffer);
        }
    }

    return 0;
}
