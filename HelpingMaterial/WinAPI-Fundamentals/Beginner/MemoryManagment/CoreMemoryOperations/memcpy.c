#include <windows.h>
#include <stdio.h>
#include <string.h>

int main() {
    printf("=== memcpy ===\n");
    
    char source[20] = "Hello World";
    char dest[20];
    
    void* result = memcpy(dest, source, 12);
    
    printf("Source Address: 0x%p\n", source);
    printf("Destination Address: 0x%p\n", dest);
    printf("Return Address: 0x%p\n", result);
    printf("Size: %lu\n", 12);
    printf("Source Buffer: %s\n", source);
    printf("Destination Buffer: %s\n", dest);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}