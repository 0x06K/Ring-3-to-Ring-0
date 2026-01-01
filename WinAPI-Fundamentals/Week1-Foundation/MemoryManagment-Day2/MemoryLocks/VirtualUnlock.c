#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualUnlock ===\n");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    VirtualLock(addr, 4096);
    
    BOOL result = VirtualUnlock(addr, 4096);
    
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    printf("Unlocked Address: 0x%p\n", addr);
    printf("Unlocked Size: %lu\n", 4096);
    
    return 0;
}