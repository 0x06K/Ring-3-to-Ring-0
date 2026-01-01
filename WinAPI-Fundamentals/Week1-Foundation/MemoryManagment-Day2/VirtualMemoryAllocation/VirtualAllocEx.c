#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualAllocEx ===\n");
    
    HANDLE hProcess = GetCurrentProcess();
    LPVOID addr = VirtualAllocEx(hProcess, NULL, 8192, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    printf("Process Handle: 0x%p\n", hProcess);
    printf("Return Address: 0x%p\n", addr);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}