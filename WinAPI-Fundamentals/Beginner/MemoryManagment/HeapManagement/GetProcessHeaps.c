#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetProcessHeaps ===\n");
    
    HANDLE heaps[64];
    DWORD count = GetProcessHeaps(64, heaps);
    
    printf("Heap Count: %lu\n", count);
    for (DWORD i = 0; i < count; i++) {
        printf("Heap[%lu]: 0x%p\n", i, heaps[i]);
    }
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}