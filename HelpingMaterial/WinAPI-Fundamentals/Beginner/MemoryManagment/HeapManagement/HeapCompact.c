#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapCompact ===\n");
    
    HANDLE hHeap = GetProcessHeap();
    SIZE_T largestFree = HeapCompact(hHeap, 0);
    
    printf("Largest Free Block: %llu\n", (unsigned long long)largestFree);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}