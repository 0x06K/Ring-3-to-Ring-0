#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== QueryMemoryResourceNotification ===\n");
    
    HANDLE resourceHandle = CreateMemoryResourceNotification(LowMemoryResourceNotification);
    BOOL state;
    
    BOOL result = QueryMemoryResourceNotification(resourceHandle, &state);
    
    printf("Return Value: %d\n", result);
    printf("Resource Handle: 0x%p\n", resourceHandle);
    printf("Memory State: %d\n", state);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}