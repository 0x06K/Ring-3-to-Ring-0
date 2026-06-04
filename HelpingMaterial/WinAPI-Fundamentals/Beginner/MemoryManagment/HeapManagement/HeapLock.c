#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapLock ===\n");
    
    HANDLE hHeap = GetProcessHeap();
    BOOL result = HeapLock(hHeap);
    
    printf("Return Value: %d\n", result);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}