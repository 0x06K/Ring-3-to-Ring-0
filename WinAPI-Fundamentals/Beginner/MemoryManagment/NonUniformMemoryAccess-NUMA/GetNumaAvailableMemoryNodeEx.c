#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetNumaAvailableMemoryNodeEx ===\n");
    
    USHORT node = 0;
    ULONGLONG availableBytes;
    
    BOOL result = GetNumaAvailableMemoryNodeEx(node, &availableBytes);
    
    printf("Return Value: %d\n", result);
    printf("Node: %u\n", node);
    printf("Available Bytes: %llu\n", availableBytes);
    printf("Available MB: %llu\n", availableBytes / (1024 * 1024));
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}