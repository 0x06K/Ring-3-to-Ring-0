#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetWriteWatch ===\n");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE | MEM_WRITE_WATCH, PAGE_READWRITE);
    
    ULONG_PTR count = 10;
    PVOID *addresses = (PVOID*)malloc(count * sizeof(PVOID));
    ULONG granularity;
    
    UINT result = GetWriteWatch(0, addr, 4096, addresses, &count, &granularity);
    
    printf("Return Value: %u\n", result);
    printf("Base Address: 0x%p\n", addr);
    printf("Region Size: %lu\n", 4096);
    printf("Addresses Array: 0x%p\n", addresses);
    printf("Count: %llu\n", count);
    printf("Granularity: %lu\n", granularity);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}