#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetNumaHighestNodeNumber ===\n");
    
    ULONG highestNodeNumber;
    
    BOOL result = GetNumaHighestNodeNumber(&highestNodeNumber);
    
    printf("Return Value: %d\n", result);
    printf("Highest Node Number: %lu\n", highestNodeNumber);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}