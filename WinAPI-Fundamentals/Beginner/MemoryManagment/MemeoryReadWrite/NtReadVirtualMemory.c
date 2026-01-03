#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtReadVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID BaseAddress,
    PVOID Buffer,
    SIZE_T BufferSize,
    PSIZE_T NumberOfBytesRead
);

int main() {
    printf("=== NtReadVirtualMemory ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtReadVirtualMemory NtReadVirtualMemory = (pNtReadVirtualMemory)GetProcAddress(ntdll, "NtReadVirtualMemory");
    
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, GetCurrentProcessId());
    char buffer[256];
    SIZE_T bytesRead;
    PVOID address = (PVOID)0x00400000;
    
    NTSTATUS status = NtReadVirtualMemory(hProcess, address, buffer, sizeof(buffer), &bytesRead);
    
    printf("NTSTATUS: 0x%08lX\n", (unsigned long)status);
    printf("Bytes Read: %llu\n", (unsigned long long)bytesRead);
    printf("Target Address: 0x%p\n", address);
    printf("Buffer Address: 0x%p\n", buffer);
    printf("Process Handle: 0x%p\n", hProcess);
    
    return 0;
}