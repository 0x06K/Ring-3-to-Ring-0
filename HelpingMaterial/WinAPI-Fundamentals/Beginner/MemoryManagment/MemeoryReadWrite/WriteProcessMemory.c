#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== WriteProcessMemory ===\n");
    
    HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());
    char data[] = "TestData";
    SIZE_T bytesWritten;
    LPVOID address = (LPVOID)0x00400000;
    
    BOOL result = WriteProcessMemory(hProcess, address, data, sizeof(data), &bytesWritten);
    
    printf("Return Value: %d\n", result);
    printf("Bytes Written: %llu\n", (unsigned long long)bytesWritten);
    printf("Target Address: 0x%p\n", address);
    printf("Source Address: 0x%p\n", data);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}