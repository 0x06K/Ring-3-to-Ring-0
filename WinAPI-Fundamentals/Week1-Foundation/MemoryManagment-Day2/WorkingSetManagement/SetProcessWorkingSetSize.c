#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== SetProcessWorkingSetSize ===\n");
    
    SIZE_T minSize = 1024 * 1024;
    SIZE_T maxSize = 4 * 1024 * 1024;
    
    BOOL result = SetProcessWorkingSetSize(GetCurrentProcess(), minSize, maxSize);
    
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    printf("Min Working Set Size: %zu\n", minSize);
    printf("Max Working Set Size: %zu\n", maxSize);
    
    return 0;
}