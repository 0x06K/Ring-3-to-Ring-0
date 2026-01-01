#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapQueryInformation ===\n");
    
    HANDLE hHeap = GetProcessHeap();
    ULONG heapFragValue = 0;
    SIZE_T returnLength = 0;
    BOOL result = HeapQueryInformation(hHeap, HeapCompatibilityInformation, &heapFragValue, sizeof(heapFragValue), &returnLength);
    
    printf("Return Value: %d\n", result);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Information Class: HeapCompatibilityInformation\n");
    printf("Value Queried: %lu\n", heapFragValue);
    printf("Return Length: %llu\n", (unsigned long long)returnLength);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}