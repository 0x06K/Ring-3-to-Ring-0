#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== HeapValidate ===\n");
    
    HANDLE hHeap = GetProcessHeap();
    LPVOID ptr = HeapAlloc(hHeap, 0, 1024);
    BOOL result = HeapValidate(hHeap, 0, ptr);
    
    printf("Return Value: %d\n", result);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Address Validated: 0x%p\n", ptr);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}