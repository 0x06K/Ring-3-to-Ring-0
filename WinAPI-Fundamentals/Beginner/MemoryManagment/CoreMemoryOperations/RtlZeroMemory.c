#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== RtlZeroMemory ===\n");
    
    char buffer[20] = "Hello World";
    
    RtlZeroMemory(buffer, 20);
    
    printf("Buffer Address: 0x%p\n", buffer);
    printf("Size: %lu\n", 20);
    printf("First 8 bytes: %02X %02X %02X %02X %02X %02X %02X %02X\n",
           buffer[0], buffer[1], buffer[2], buffer[3],
           buffer[4], buffer[5], buffer[6], buffer[7]);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}