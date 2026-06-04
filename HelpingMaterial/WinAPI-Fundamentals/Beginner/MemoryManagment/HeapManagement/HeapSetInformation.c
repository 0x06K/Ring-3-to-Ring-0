#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapSetInformation ===\n");
    
    HANDLE hHeap = GetProcessHeap();
    ULONG heapFragValue = 2;
    BOOL result = HeapSetInformation(hHeap, HeapCompatibilityInformation, &heapFragValue, sizeof(heapFragValue));
    
    printf("Return Value: %d\n", result);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Information Class: HeapCompatibilityInformation\n");
    printf("Value Set: %lu\n", heapFragValue);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}