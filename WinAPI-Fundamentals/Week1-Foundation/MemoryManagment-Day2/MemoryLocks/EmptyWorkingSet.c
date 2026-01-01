#include <windows.h>
#include <stdio.h>
#include <psapi.h>

int main() {
    printf("=== EmptyWorkingSet ===\n");
    
    BOOL result = EmptyWorkingSet(GetCurrentProcess());
    
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    
    return 0;
}