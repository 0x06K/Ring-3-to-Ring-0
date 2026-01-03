#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== MapUserPhysicalPagesScatter ===\n");
    
    ULONG_PTR numberOfPages = 5;
    PULONG_PTR pageArray = (PULONG_PTR)malloc(numberOfPages * sizeof(ULONG_PTR));
    AllocateUserPhysicalPages(GetCurrentProcess(), &numberOfPages, pageArray);
    
    PVOID *virtualAddresses = (PVOID*)malloc(numberOfPages * sizeof(PVOID));
    for (ULONG_PTR i = 0; i < numberOfPages; i++) {
        virtualAddresses[i] = VirtualAlloc(NULL, 4096, MEM_RESERVE | MEM_PHYSICAL, PAGE_READWRITE);
    }
    
    BOOL result = MapUserPhysicalPagesScatter(virtualAddresses, numberOfPages, pageArray);
    
    printf("Return Value: %d\n", result);
    printf("Number of Pages: %llu\n", numberOfPages);
    printf("Virtual Addresses Array: 0x%p\n", virtualAddresses);
    printf("Page Array Address: 0x%p\n", pageArray);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}