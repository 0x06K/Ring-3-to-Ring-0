#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetNumaProximityNodeEx ===\n");
    
    ULONG proximityId = 0;
    USHORT nodeNumber;
    
    BOOL result = GetNumaProximityNodeEx(proximityId, &nodeNumber);
    
    printf("Return Value: %d\n", result);
    printf("Proximity ID: %lu\n", proximityId);
    printf("Node Number: %u\n", nodeNumber);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}