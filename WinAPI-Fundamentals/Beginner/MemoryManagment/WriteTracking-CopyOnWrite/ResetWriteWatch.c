#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== ResetWriteWatch ===\n");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE | MEM_WRITE_WATCH, PAGE_READWRITE);
    
    UINT result = ResetWriteWatch(addr, 4096);
    
    printf("Return Value: %u\n", result);
    printf("Base Address: 0x%p\n", addr);
    printf("Region Size: %lu\n", 4096);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}