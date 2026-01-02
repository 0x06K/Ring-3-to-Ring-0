#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== SetProcessWorkingSetSizeEx ===\n");
    
    SIZE_T minSize = 1024 * 1024;
    SIZE_T maxSize = 4 * 1024 * 1024;
    DWORD flags = QUOTA_LIMITS_HARDWS_MIN_ENABLE | QUOTA_LIMITS_HARDWS_MAX_DISABLE;
    
    BOOL result = SetProcessWorkingSetSizeEx(GetCurrentProcess(), minSize, maxSize, flags);
    
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    printf("Min Working Set Size: %zu\n", minSize);
    printf("Max Working Set Size: %zu\n", maxSize);
    printf("Flags: 0x%08lx\n", flags);
    
    return 0;
}