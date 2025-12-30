#include <windows.h>
#include <winternl.h>
#include <stdio.h>


typedef NTSTATUS (NTAPI *pNtQueryInformationProcess)(
    HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);

int main() {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    pNtQueryInformationProcess NtQIP = (pNtQueryInformationProcess)GetProcAddress(ntdll, "NtQueryInformationProcess");

    PROCESS_BASIC_INFORMATION pbi = {0};
    NTSTATUS status = NtQIP(GetCurrentProcess(), ProcessBasicInformation, &pbi, sizeof(pbi), NULL);

    if(status == 0) {
        printf("Current PID: %llu\n", (ULONG_PTR)pbi.UniqueProcessId);
        printf("PEB Address: %p\n", pbi.PebBaseAddress);
    }

    return 0;
}
