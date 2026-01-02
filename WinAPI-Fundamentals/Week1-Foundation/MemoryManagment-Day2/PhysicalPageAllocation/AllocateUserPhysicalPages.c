#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== AllocateUserPhysicalPages ===\n");
    
    ULONG_PTR numberOfPages = 10;
    PULONG_PTR pageArray = (PULONG_PTR)malloc(numberOfPages * sizeof(ULONG_PTR));
    
    BOOL result = AllocateUserPhysicalPages(GetCurrentProcess(), &numberOfPages, pageArray);
    
    printf("Return Value: %d\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Requested Pages: %llu\n", 10ULL);
    printf("Allocated Pages: %llu\n", numberOfPages);
    printf("Page Array Address: 0x%p\n", pageArray);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}