#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== WriteProcessMemory ===\n");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    int dataToWrite = 67890;
    SIZE_T bytesWritten;
    
    BOOL result = WriteProcessMemory(GetCurrentProcess(), addr, &dataToWrite, 
                                     sizeof(int), &bytesWritten);
    
    printf("Return Value: %d\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Base Address: 0x%p\n", addr);
    printf("Buffer Address: 0x%p\n", &dataToWrite);
    printf("Size: %zu\n", sizeof(int));
    printf("Bytes Written: %zu\n", bytesWritten);
    printf("Data Written: %d\n", dataToWrite);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}