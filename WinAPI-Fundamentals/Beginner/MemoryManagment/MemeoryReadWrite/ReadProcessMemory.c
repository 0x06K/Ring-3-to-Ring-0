#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== ReadProcessMemory ===\n");
    
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, GetCurrentProcessId());
    char buffer[256];
    SIZE_T bytesRead;
    LPVOID address = (LPVOID)0x00400000;
    
    BOOL result = ReadProcessMemory(hProcess, address, buffer, sizeof(buffer), &bytesRead);
    
    printf("Return Value: %d\n", result);
    printf("Bytes Read: %llu\n", (unsigned long long)bytesRead);
    printf("Target Address: 0x%p\n", address);
    printf("Buffer Address: 0x%p\n", buffer);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}