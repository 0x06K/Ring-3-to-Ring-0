#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GlobalMemoryStatusEx ===\n");
    
    MEMORYSTATUSEX mse;
    mse.dwLength = sizeof(mse);
    BOOL result = GlobalMemoryStatusEx(&mse);
    
    printf("Return Value: %d\n", result);
    printf("Length: %lu\n", mse.dwLength);
    printf("Memory Load: %lu%%\n", mse.dwMemoryLoad);
    printf("Total Physical: %llu bytes\n", mse.ullTotalPhys);
    printf("Available Physical: %llu bytes\n", mse.ullAvailPhys);
    printf("Total Page File: %llu bytes\n", mse.ullTotalPageFile);
    printf("Available Page File: %llu bytes\n", mse.ullAvailPageFile);
    printf("Total Virtual: %llu bytes\n", mse.ullTotalVirtual);
    printf("Available Virtual: %llu bytes\n", mse.ullAvailVirtual);
    printf("Available Extended Virtual: %llu bytes\n", mse.ullAvailExtendedVirtual);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}