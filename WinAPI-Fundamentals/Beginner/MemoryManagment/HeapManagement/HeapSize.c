#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapSize ===\n");
    
    HANDLE hHeap = GetProcessHeap();
    LPVOID ptr = HeapAlloc(hHeap, 0, 1024);
    SIZE_T size = HeapSize(hHeap, 0, ptr);
    
    printf("Allocation Size: %llu\n", (unsigned long long)size);
    printf("Address: 0x%p\n", ptr);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}