#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualAllocExNuma with MEM_LARGE_PAGES ===\n");
    
    SIZE_T largePageSize = GetLargePageMinimum();
    DWORD numaNode = 0;
    
    LPVOID result = VirtualAllocExNuma(GetCurrentProcess(), NULL, largePageSize, 
                                       MEM_COMMIT | MEM_RESERVE | MEM_LARGE_PAGES, 
                                       PAGE_READWRITE, numaNode);
    
    printf("Return Address: 0x%p\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Requested Size: %zu\n", largePageSize);
    printf("NUMA Node: %lu\n", numaNode);
    printf("Allocation Type: MEM_COMMIT | MEM_RESERVE | MEM_LARGE_PAGES\n");
    printf("Protection: PAGE_READWRITE\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}