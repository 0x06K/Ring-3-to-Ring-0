#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapReAlloc ===\n");
    
    HANDLE hHeap = GetProcessHeap();
    LPVOID ptr = HeapAlloc(hHeap, 0, 1024);
    LPVOID newPtr = HeapReAlloc(hHeap, 0, ptr, 2048);
    
    printf("Original Address: 0x%p\n", ptr);
    printf("New Address: 0x%p\n", newPtr);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("New Size: 2048\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}