#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapWalk ===\n");
    
    HANDLE hHeap = GetProcessHeap();
    PROCESS_HEAP_ENTRY entry;
    entry.lpData = NULL;
    
    BOOL result = HeapWalk(hHeap, &entry);
    
    printf("Return Value: %d\n", result);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Entry Address: 0x%p\n", entry.lpData);
    printf("Entry Size: %llu\n", (unsigned long long)entry.cbData);
    printf("Entry Overhead: %u\n", (unsigned int)entry.cbOverhead);
    printf("Entry Region Index: %u\n", (unsigned int)entry.iRegionIndex);
    printf("Entry Flags: 0x%04X\n", (unsigned int)entry.wFlags);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}