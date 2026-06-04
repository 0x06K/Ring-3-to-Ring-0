#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== FlushInstructionCache ===\n");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    
    BOOL result = FlushInstructionCache(GetCurrentProcess(), addr, 4096);
    
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Base Address: 0x%p\n", addr);
    printf("Size: %lu\n", 4096);
    
    return 0;
}