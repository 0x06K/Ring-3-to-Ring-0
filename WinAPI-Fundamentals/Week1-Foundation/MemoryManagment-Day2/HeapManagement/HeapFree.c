#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapFree ===\n");
    
    HANDLE hHeap = GetProcessHeap();
    LPVOID ptr = HeapAlloc(hHeap, 0, 1024);
    BOOL result = HeapFree(hHeap, 0, ptr);
    
    printf("Return Value: %d\n", result);
    printf("Freed Address: 0x%p\n", ptr);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}