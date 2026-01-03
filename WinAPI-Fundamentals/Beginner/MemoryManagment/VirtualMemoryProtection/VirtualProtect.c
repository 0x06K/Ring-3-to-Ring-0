#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualProtect ===\n");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    DWORD oldProtect;
    BOOL result = VirtualProtect(addr, 4096, PAGE_EXECUTE_READ, &oldProtect);
    
    printf("Address: 0x%p\n", addr);
    printf("New Protection: PAGE_EXECUTE_READ\n");
    printf("Old Protection: 0x%lX\n", oldProtect);
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}