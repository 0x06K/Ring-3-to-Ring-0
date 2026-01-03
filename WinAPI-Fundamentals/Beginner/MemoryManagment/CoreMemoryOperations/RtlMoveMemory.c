#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== RtlMoveMemory ===\n");
    
    char buffer[20] = "Hello World";
    
    RtlMoveMemory(buffer + 6, buffer, 5);
    
    printf("Source Address: 0x%p\n", buffer);
    printf("Destination Address: 0x%p\n", buffer + 6);
    printf("Size: %lu\n", 5);
    printf("Result Buffer: %s\n", buffer);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}