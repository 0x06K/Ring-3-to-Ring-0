#include <windows.h>
#include <stdio.h>
#include <string.h>

int main() {
    printf("=== memset ===\n");
    
    char buffer[20];
    
    void* result = memset(buffer, 0xBB, 20);
    
    printf("Buffer Address: 0x%p\n", buffer);
    printf("Return Address: 0x%p\n", result);
    printf("Size: %lu\n", 20);
    printf("Fill Byte: 0x%02X\n", 0xBB);
    printf("First 8 bytes: %02X %02X %02X %02X %02X %02X %02X %02X\n",
           buffer[0], buffer[1], buffer[2], buffer[3],
           buffer[4], buffer[5], buffer[6], buffer[7]);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}