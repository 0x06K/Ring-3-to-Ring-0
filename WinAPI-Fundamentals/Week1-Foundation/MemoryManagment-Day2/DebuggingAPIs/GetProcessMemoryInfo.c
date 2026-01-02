#include <windows.h>
#include <stdio.h>
#include <psapi.h>

int main() {
    printf("=== GetProcessMemoryInfo ===\n");
    
    PROCESS_MEMORY_COUNTERS pmc;
    
    BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    
    printf("Return Value: %d\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("PageFaultCount: %lu\n", pmc.PageFaultCount);
    printf("PeakWorkingSetSize: %zu\n", pmc.PeakWorkingSetSize);
    printf("WorkingSetSize: %zu\n", pmc.WorkingSetSize);
    printf("QuotaPeakPagedPoolUsage: %zu\n", pmc.QuotaPeakPagedPoolUsage);
    printf("QuotaPagedPoolUsage: %zu\n", pmc.QuotaPagedPoolUsage);
    printf("QuotaPeakNonPagedPoolUsage: %zu\n", pmc.QuotaPeakNonPagedPoolUsage);
    printf("QuotaNonPagedPoolUsage: %zu\n", pmc.QuotaNonPagedPoolUsage);
    printf("PagefileUsage: %zu\n", pmc.PagefileUsage);
    printf("PeakPagefileUsage: %zu\n", pmc.PeakPagefileUsage);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}