#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualFree ===\n");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    BOOL result = VirtualFree(addr, 0, MEM_RELEASE);
    
    printf("Address Freed: 0x%p\n", addr);
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}