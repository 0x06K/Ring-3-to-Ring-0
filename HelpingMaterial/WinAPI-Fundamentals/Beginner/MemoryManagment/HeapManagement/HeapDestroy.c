#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapDestroy ===\n");
    
    HANDLE hHeap = HeapCreate(0, 4096, 0);
    BOOL result = HeapDestroy(hHeap);
    
    printf("Return Value: %d\n", result);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}