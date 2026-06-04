#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualLock ===\n");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    BOOL result = VirtualLock(addr, 4096);
    
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    printf("Locked Address: 0x%p\n", addr);
    printf("Locked Size: %lu\n", 4096);
    
    return 0;
}