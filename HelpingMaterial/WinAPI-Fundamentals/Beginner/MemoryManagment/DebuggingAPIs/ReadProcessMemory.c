#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== ReadProcessMemory ===\n");
    
    int localVar = 12345;
    int readValue;
    SIZE_T bytesRead;
    
    BOOL result = ReadProcessMemory(GetCurrentProcess(), &localVar, &readValue, 
                                    sizeof(int), &bytesRead);
    
    printf("Return Value: %d\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Base Address: 0x%p\n", &localVar);
    printf("Buffer Address: 0x%p\n", &readValue);
    printf("Size: %zu\n", sizeof(int));
    printf("Bytes Read: %zu\n", bytesRead);
    printf("Read Value: %d\n", readValue);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}