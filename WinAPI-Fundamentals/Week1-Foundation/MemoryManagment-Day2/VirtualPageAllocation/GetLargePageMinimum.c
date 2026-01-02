#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetLargePageMinimum ===\n");
    
    SIZE_T result = GetLargePageMinimum();
    
    printf("Large Page Minimum Size: %zu\n", result);
    printf("Large Page Size (MB): %zu\n", result / (1024 * 1024));
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}