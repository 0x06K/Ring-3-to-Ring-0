#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualAlloc with MEM_LARGE_PAGES ===\n");
    
    SIZE_T largePageSize = GetLargePageMinimum();
    
    LPVOID result = VirtualAlloc(NULL, largePageSize, MEM_COMMIT | MEM_RESERVE | MEM_LARGE_PAGES, PAGE_READWRITE);
    
    printf("Return Address: 0x%p\n", result);
    printf("Requested Size: %zu\n", largePageSize);
    printf("Allocation Type: MEM_COMMIT | MEM_RESERVE | MEM_LARGE_PAGES\n");
    printf("Protection: PAGE_READWRITE\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}