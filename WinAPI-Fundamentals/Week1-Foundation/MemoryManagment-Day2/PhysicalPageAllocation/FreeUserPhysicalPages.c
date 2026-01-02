#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== FreeUserPhysicalPages ===\n");
    
    ULONG_PTR numberOfPages = 10;
    PULONG_PTR pageArray = (PULONG_PTR)malloc(numberOfPages * sizeof(ULONG_PTR));
    AllocateUserPhysicalPages(GetCurrentProcess(), &numberOfPages, pageArray);
    
    ULONG_PTR pagesToFree = numberOfPages;
    BOOL result = FreeUserPhysicalPages(GetCurrentProcess(), &pagesToFree, pageArray);
    
    printf("Return Value: %d\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Pages to Free: %llu\n", numberOfPages);
    printf("Pages Freed: %llu\n", pagesToFree);
    printf("Page Array Address: 0x%p\n", pageArray);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}