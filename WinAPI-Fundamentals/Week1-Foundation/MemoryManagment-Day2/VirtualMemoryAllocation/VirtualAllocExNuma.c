#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualAllocExNuma ===\n");
    
    LPVOID addr = VirtualAllocExNuma(GetCurrentProcess(), NULL, 4096, 
                                      MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE, 0);
    
    printf("Return Address: 0x%p\n", addr);
    printf("NUMA Node: 0\n");
    printf("Error Code: %lu\n", GetLastError());
    
    if (addr) {
        VirtualFreeEx(GetCurrentProcess(), addr, 0, MEM_RELEASE);
    }
    
    return 0;
}