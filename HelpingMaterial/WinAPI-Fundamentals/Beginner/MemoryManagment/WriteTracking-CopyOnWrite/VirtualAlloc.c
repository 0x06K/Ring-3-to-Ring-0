#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualAlloc with MEM_WRITE_WATCH ===\n");
    
    LPVOID result = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE | MEM_WRITE_WATCH, PAGE_READWRITE);
    
    printf("Return Address: 0x%p\n", result);
    printf("Size: %lu\n", 4096);
    printf("Allocation Type: MEM_COMMIT | MEM_RESERVE | MEM_WRITE_WATCH\n");
    printf("Protection: PAGE_READWRITE\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}