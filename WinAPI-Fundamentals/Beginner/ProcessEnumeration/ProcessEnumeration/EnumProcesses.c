/***************************************************************
 *  EnumArrayPSAPI (psapi.h)
 *
 *  Description:
 *      Retrieves the process identifiers (PIDs) of all active
 *      processes in the system.
 *
 *  Prototype:
 *      BOOL EnumProcesses(
 *          DWORD   *lpidProcess,
 *          DWORD   cb,
 *          LPDWORD lpcbNeeded
 *      );
 *      LPDWORD is just a Windows-defined type alias, and it means:
 *      “Long Pointer to a DWORD”. in modern terms: DWORD*
 *  Parameters:
 *      lpidProcess
 *          Pointer to a buffer that receives process IDs.
 *
 *      cb
 *          Size of the buffer in bytes.
 *
 *      lpcbNeeded
 *          Receives the number of bytes written or required.
 *          If this value >= cb, the buffer was too small.
 *
 *  Return Value:
 *      Non-zero on success.
 *      Zero on failure (use GetLastError()).
 *
 *  Notes:
 *      - Only process IDs are returned (no names or paths).
 *      - The process list is a snapshot and may change at any time.
 *      - Reallocate and retry if the buffer is insufficient.
 *      - Requires <windows.h> and <psapi.h>.
 ***************************************************************/




#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#include "colors.h"


void EnableANSIColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (hOut == INVALID_HANDLE_VALUE) return;

    if (GetConsoleMode(hOut, &dwMode)) {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
}


int main(){
    EnableANSIColors();
    printf(CLR_BOLD CLR_GREEN "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf(CLR_BOLD CLR_GREEN "||              P R O C E S S  E N U M E R A T O R              ||\n");
    printf(CLR_BOLD CLR_GREEN "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" CLR_RESET);
    
    DWORD processes[1024] = {0};
    DWORD bytesReturned = 0;

    if (!EnumProcesses(processes, sizeof(processes), &bytesReturned)) {
        printf("EnumProcesses failed. Error: %lu\n", GetLastError());
        return 1;
    }

    DWORD processCount = bytesReturned / sizeof(DWORD);

    printf("Number of processes: %lu\n\nHere is PID of first 5 processes:\n", bytesReturned);

    for (DWORD i = 0; i < 5; i++) {
        DWORD pid = processes[i];

        if (pid == 0)
            continue;

        printf("PID: %lu\n", pid);
    }
    
    return 0;
}