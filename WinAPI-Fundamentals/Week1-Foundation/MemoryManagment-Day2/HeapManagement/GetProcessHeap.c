#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetProcessHeap ===\n");
    
    HANDLE hHeap = GetProcessHeap();
    
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}