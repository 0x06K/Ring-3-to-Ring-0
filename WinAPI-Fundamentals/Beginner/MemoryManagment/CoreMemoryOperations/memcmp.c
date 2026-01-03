#include <windows.h>
#include <stdio.h>
#include <string.h>

int main() {
    printf("=== memcmp ===\n");
    
    char buffer1[20] = "Hello World";
    char buffer2[20] = "Hello There";
    
    int result = memcmp(buffer1, buffer2, 20);
    
    printf("Buffer1 Address: 0x%p\n", buffer1);
    printf("Buffer2 Address: 0x%p\n", buffer2);
    printf("Size: %lu\n", 20);
    printf("Return Value: %d\n", result);
    printf("Buffer1: %s\n", buffer1);
    printf("Buffer2: %s\n", buffer2);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}