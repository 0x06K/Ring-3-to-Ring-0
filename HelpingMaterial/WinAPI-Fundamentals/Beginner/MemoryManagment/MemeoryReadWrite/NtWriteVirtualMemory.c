#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtWriteVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID BaseAddress,
    PVOID Buffer,
    SIZE_T BufferSize,
    PSIZE_T NumberOfBytesWritten
);

int main() {
    printf("=== NtWriteVirtualMemory ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtWriteVirtualMemory NtWriteVirtualMemory = (pNtWriteVirtualMemory)GetProcAddress(ntdll, "NtWriteVirtualMemory");
    
    HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());
    char data[] = "TestData";
    SIZE_T bytesWritten;
    PVOID address = (PVOID)0x00400000;
    
    NTSTATUS status = NtWriteVirtualMemory(hProcess, address, data, sizeof(data), &bytesWritten);
    
    printf("NTSTATUS: 0x%08lX\n", (unsigned long)status);
    printf("Bytes Written: %llu\n", (unsigned long long)bytesWritten);
    printf("Target Address: 0x%p\n", address);
    printf("Source Address: 0x%p\n", data);
    printf("Process Handle: 0x%p\n", hProcess);
    
    return 0;
}