#include <windows.h>
#include <wtsapi32.h>
#include <stdio.h>

#pragma comment(lib, "wtsapi32.lib")

int main() {
    PWTS_PROCESS_INFOA pProcessInfo = NULL;
    DWORD dwCount = 0;
    
    printf("[+] Enumerating processes using WTSEnumerateProcesses...\n\n");
    
    if (!WTSEnumerateProcessesA(WTS_CURRENT_SERVER_HANDLE, 0, 1, &pProcessInfo, &dwCount)) {
        printf("[-] WTSEnumerateProcessesA failed: %lu\n", GetLastError());
        return 1;
    }

    printf("%-8s %-8s %-40s\n", "PID", "Session", "Process Name");
    printf("================================================================\n");

    for (DWORD i = 0; i < dwCount; i++) {
        printf("%-8lu %-8lu %-40s\n", pProcessInfo[i].ProcessId, pProcessInfo[i].SessionId, pProcessInfo[i].pProcessName ? pProcessInfo[i].pProcessName : "<Unknown>");
    }

    WTSFreeMemory(pProcessInfo);
    
    printf("\n[+] Total: %lu processes\n", dwCount);
    return 0;
}