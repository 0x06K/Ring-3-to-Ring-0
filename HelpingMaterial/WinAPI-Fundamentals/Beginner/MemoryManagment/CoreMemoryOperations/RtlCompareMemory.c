#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== RtlCompareMemory ===\n");
    
    char buffer1[20] = "Hello World";
    char buffer2[20] = "Hello There";
    
    SIZE_T result = RtlCompareMemory(buffer1, buffer2, 20);
    
    printf("Buffer1 Address: 0x%p\n", buffer1);
    printf("Buffer2 Address: 0x%p\n", buffer2);
    printf("Size: %lu\n", 20);
    printf("Matching Bytes: %zu\n", result);
    printf("Buffer1: %s\n", buffer1);
    printf("Buffer2: %s\n", buffer2);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}