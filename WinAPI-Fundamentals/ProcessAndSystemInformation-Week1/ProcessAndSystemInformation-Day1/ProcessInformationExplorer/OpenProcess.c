#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#include "colors.h"


void ListProcesses()
{
    DWORD pids[1024], bytesReturned;
    if (!EnumProcesses(pids, sizeof(pids), &bytesReturned))
        return;

    int count = bytesReturned / sizeof(DWORD);

    printf(CLR_BOLD CLR_CYAN "\n[+] Active Processes\n" CLR_RESET);
    for (int i = 0; i < count; i++)
    {
        if (pids[i] != 0)
            printf(CLR_GREEN "  PID: %lu\n" CLR_RESET, pids[i]);
    }
}

void ShowProcessInfo(DWORD pid)
{
    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

    if (!hProc)
    {
        printf(CLR_RED "[-] Failed to open PID %lu (Access Denied)\n" CLR_RESET, pid);
        return;
    }

    char name[MAX_PATH] = "Unknown";
    GetModuleFileNameExA(hProc, NULL, name, MAX_PATH);

    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(hProc, &pmc, sizeof(pmc));

    printf(CLR_BOLD CLR_GREEN "\n[+] PROCESS INFO\n" CLR_RESET);
    printf(CLR_CYAN "PID        : %lu\n" CLR_RESET, pid);
    printf(CLR_CYAN "Image Path : %s\n" CLR_RESET, name);
    printf(CLR_CYAN "Memory     : %lu KB\n" CLR_RESET, pmc.WorkingSetSize / 1024);

    CloseHandle(hProc);
}

int main()
{
    EnableANSI();

    int choice;
    DWORD pid;

    do
    {
        printf(CLR_BOLD CLR_YELLOW "\n==== MINI PROCESS VIEWER ====\n" CLR_RESET);
        printf(CLR_CYAN "1. List all processes\n" CLR_RESET);
        printf(CLR_CYAN "2. Inspect process by PID\n" CLR_RESET);
        printf(CLR_CYAN "0. Exit\n" CLR_RESET);
        printf(CLR_BOLD "> " CLR_RESET);

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            ListProcesses();
            break;

        case 2:
            printf(CLR_YELLOW "Enter PID: " CLR_RESET);
            scanf("%lu", &pid);
            ShowProcessInfo(pid);
            break;

        case 0:
            printf(CLR_RED "Exiting...\n" CLR_RESET);
            break;

        default:
            printf(CLR_RED "Invalid option!\n" CLR_RESET);
        }

    } while (choice != 0);

    return 0;
}
