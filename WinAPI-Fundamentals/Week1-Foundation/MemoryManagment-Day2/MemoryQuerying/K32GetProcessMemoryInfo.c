#include <windows.h>
#include <psapi.h>
#include <stdio.h>

int main() {
    printf("=== K32GetProcessMemoryInfo ===\n");
    
    HANDLE hProcess = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS pmc;
    BOOL result = K32GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
    
    printf("Process Handle: 0x%p\n", hProcess);
    printf("Return Value: %d\n", result);
    printf("Page Fault Count: %lu\n", pmc.PageFaultCount);
    printf("Peak Working Set Size: %zu bytes\n", pmc.PeakWorkingSetSize);
    printf("Working Set Size: %zu bytes\n", pmc.WorkingSetSize);
    printf("Quota Peak Paged Pool Usage: %zu bytes\n", pmc.QuotaPeakPagedPoolUsage);
    printf("Quota Paged Pool Usage: %zu bytes\n", pmc.QuotaPagedPoolUsage);
    printf("Quota Peak Non-Paged Pool Usage: %zu bytes\n", pmc.QuotaPeakNonPagedPoolUsage);
    printf("Quota Non-Paged Pool Usage: %zu bytes\n", pmc.QuotaNonPagedPoolUsage);
    printf("Page File Usage: %zu bytes\n", pmc.PagefileUsage);
    printf("Peak Page File Usage: %zu bytes\n", pmc.PeakPagefileUsage);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}