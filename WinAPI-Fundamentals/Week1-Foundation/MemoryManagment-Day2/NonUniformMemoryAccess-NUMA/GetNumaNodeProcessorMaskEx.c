#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetNumaNodeProcessorMaskEx ===\n");
    
    USHORT node = 0;
    GROUP_AFFINITY processorMask;
    
    BOOL result = GetNumaNodeProcessorMaskEx(node, &processorMask);
    
    printf("Return Value: %d\n", result);
    printf("Node: %u\n", node);
    printf("Group: %u\n", processorMask.Group);
    printf("Mask: 0x%016llx\n", processorMask.Mask);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}