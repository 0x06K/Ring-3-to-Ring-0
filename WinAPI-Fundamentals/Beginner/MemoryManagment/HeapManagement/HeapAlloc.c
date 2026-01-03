#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapAlloc ===\n");
    
    HANDLE hHeap = GetProcessHeap();
    LPVOID ptr = HeapAlloc(hHeap, 0, 1024);
    
    printf("Allocated Address: 0x%p\n", ptr);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Size Requested: 1024\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}