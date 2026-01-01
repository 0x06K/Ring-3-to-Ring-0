#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapUnlock ===\n");
    
    HANDLE hHeap = GetProcessHeap();
    HeapLock(hHeap);
    BOOL result = HeapUnlock(hHeap);
    
    printf("Return Value: %d\n", result);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}