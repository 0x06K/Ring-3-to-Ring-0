#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualAlloc ===\n");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    printf("Return Address: 0x%p\n", addr);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}