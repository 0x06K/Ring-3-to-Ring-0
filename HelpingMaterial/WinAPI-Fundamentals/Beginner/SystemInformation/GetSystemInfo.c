#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetSystemInfo ===\n");
    
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    
    printf("Processor Architecture: %u\n", si.wProcessorArchitecture);
    printf("Page Size: %lu bytes\n", si.dwPageSize);
    printf("Minimum Application Address: 0x%p\n", si.lpMinimumApplicationAddress);
    printf("Maximum Application Address: 0x%p\n", si.lpMaximumApplicationAddress);
    printf("Active Processor Mask: 0x%IX\n", si.dwActiveProcessorMask);
    printf("Number of Processors: %lu\n", si.dwNumberOfProcessors);
    printf("Processor Type: %lu\n", si.dwProcessorType);
    printf("Allocation Granularity: %lu bytes\n", si.dwAllocationGranularity);
    printf("Processor Level: %u\n", si.wProcessorLevel);
    printf("Processor Revision: %u\n", si.wProcessorRevision);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}