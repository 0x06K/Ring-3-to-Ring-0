#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== CreateMemoryResourceNotification ===\n");
    
    HANDLE result = CreateMemoryResourceNotification(LowMemoryResourceNotification);
    
    printf("Return Handle: 0x%p\n", result);
    printf("Notification Type: LowMemoryResourceNotification (%d)\n", LowMemoryResourceNotification);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}