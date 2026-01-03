#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GlobalMemoryStatus (Deprecated) ===\n");
    
    MEMORYSTATUS ms;
    GlobalMemoryStatus(&ms);
    
    printf("Length: %lu\n", ms.dwLength);
    printf("Memory Load: %lu%%\n", ms.dwMemoryLoad);
    printf("Total Physical: %lu bytes\n", ms.dwTotalPhys);
    printf("Available Physical: %lu bytes\n", ms.dwAvailPhys);
    printf("Total Page File: %lu bytes\n", ms.dwTotalPageFile);
    printf("Available Page File: %lu bytes\n", ms.dwAvailPageFile);
    printf("Total Virtual: %lu bytes\n", ms.dwTotalVirtual);
    printf("Available Virtual: %lu bytes\n", ms.dwAvailVirtual);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}