#include <windows.h>
#include <stdio.h>

typedef BOOL (WINAPI *pGetMemoryErrorHandlingCapabilities)(PULONG Capabilities);

int main() {
    printf("=== GetMemoryErrorHandlingCapabilities ===\n");
    
    HMODULE kernel32 = LoadLibraryA("kernel32.dll");
    pGetMemoryErrorHandlingCapabilities GetMemoryErrorHandlingCapabilities = 
        (pGetMemoryErrorHandlingCapabilities)GetProcAddress(kernel32, "GetMemoryErrorHandlingCapabilities");
    
    ULONG capabilities;
    
    BOOL result = GetMemoryErrorHandlingCapabilities(&capabilities);
    
    printf("Return Value: %d\n", result);
    printf("Capabilities: 0x%08lx\n", capabilities);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}