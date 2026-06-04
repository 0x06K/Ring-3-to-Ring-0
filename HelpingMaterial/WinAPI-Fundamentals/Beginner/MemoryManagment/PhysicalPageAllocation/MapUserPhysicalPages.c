#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== MapUserPhysicalPages ===\n");
    
    ULONG_PTR numberOfPages = 10;
    PULONG_PTR pageArray = (PULONG_PTR)malloc(numberOfPages * sizeof(ULONG_PTR));
    AllocateUserPhysicalPages(GetCurrentProcess(), &numberOfPages, pageArray);
    
    SIZE_T regionSize = numberOfPages * 4096;
    LPVOID virtualAddr = VirtualAlloc(NULL, regionSize, MEM_RESERVE | MEM_PHYSICAL, PAGE_READWRITE);
    
    BOOL result = MapUserPhysicalPages(virtualAddr, numberOfPages, pageArray);
    
    printf("Return Value: %d\n", result);
    printf("Virtual Address: 0x%p\n", virtualAddr);
    printf("Number of Pages: %llu\n", numberOfPages);
    printf("Page Array Address: 0x%p\n", pageArray);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}