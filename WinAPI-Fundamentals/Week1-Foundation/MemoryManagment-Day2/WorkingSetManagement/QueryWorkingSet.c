#include <windows.h>
#include <stdio.h>
#include <psapi.h>

int main() {
    printf("=== QueryWorkingSet ===\n");
    
    DWORD bufferSize = 4096;
    PVOID buffer = malloc(bufferSize);
    
    BOOL result = QueryWorkingSet(GetCurrentProcess(), buffer, bufferSize);
    
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    printf("Buffer Address: 0x%p\n", buffer);
    printf("Buffer Size: %lu\n", bufferSize);
    
    return 0;
}