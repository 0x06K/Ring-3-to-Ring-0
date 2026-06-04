#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualFreeEx ===\n");
    
    HANDLE hProcess = GetCurrentProcess();
    LPVOID addr = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    BOOL result = VirtualFreeEx(hProcess, addr, 0, MEM_RELEASE);
    
    printf("Process Handle: 0x%p\n", hProcess);
    printf("Address Freed: 0x%p\n", addr);
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}