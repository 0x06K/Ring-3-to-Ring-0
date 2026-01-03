#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapCreate ===\n");
    
    HANDLE hHeap = HeapCreate(0, 4096, 0);
    
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}