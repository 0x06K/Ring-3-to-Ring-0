#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== AllocateUserPhysicalPagesNuma ===\n");
    
    ULONG_PTR numberOfPages = 10;
    PULONG_PTR pageArray = (PULONG_PTR)malloc(numberOfPages * sizeof(ULONG_PTR));
    DWORD numaNode = 0;
    
    BOOL result = AllocateUserPhysicalPagesNuma(GetCurrentProcess(), &numberOfPages, pageArray, numaNode);
    
    printf("Return Value: %d\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Requested Pages: %llu\n", 10ULL);
    printf("Allocated Pages: %llu\n", numberOfPages);
    printf("Page Array Address: 0x%p\n", pageArray);
    printf("NUMA Node: %lu\n", numaNode);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}