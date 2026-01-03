#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetProcessWorkingSetSize ===\n");
    
    SIZE_T minSize;
    SIZE_T maxSize;
    
    BOOL result = GetProcessWorkingSetSize(GetCurrentProcess(), &minSize, &maxSize);
    
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    printf("Min Working Set Size: %zu\n", minSize);
    printf("Max Working Set Size: %zu\n", maxSize);
    
    return 0;
}