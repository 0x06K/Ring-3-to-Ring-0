#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetNumaNodeProcessorMask ===\n");
    
    UCHAR node = 0;
    ULONGLONG processorMask;
    
    BOOL result = GetNumaNodeProcessorMask(node, &processorMask);
    
    printf("Return Value: %d\n", result);
    printf("Node: %u\n", node);
    printf("Processor Mask: 0x%016llx\n", processorMask);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}