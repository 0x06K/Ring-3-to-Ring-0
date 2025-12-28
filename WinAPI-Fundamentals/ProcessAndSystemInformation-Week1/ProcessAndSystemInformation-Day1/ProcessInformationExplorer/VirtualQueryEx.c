#include <windows.h>
#include <stdio.h>
#include <psapi.h>
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

void ScanMemory(HANDLE hProcess)
{
    MEMORY_BASIC_INFORMATION mbi;
    unsigned char buffer[64];

    unsigned char* addr = 0;

    while (VirtualQueryEx(hProcess, addr, &mbi, sizeof(mbi)) == sizeof(mbi))
    {
        // Only read committed, readable memory
        if (mbi.State == MEM_COMMIT && (mbi.Protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE)))
        {
            SIZE_T bytesRead;

            if (ReadProcessMemory(hProcess, mbi.BaseAddress, buffer, sizeof(buffer), &bytesRead))
            {
                printf("Region: 0x%p | Size: %llu | Read %llu bytes\n",
                       mbi.BaseAddress,
                       (unsigned long long)mbi.RegionSize,
                       (unsigned long long)bytesRead);
            }
        }
        // Move to next memory region
        addr = (unsigned char*)mbi.BaseAddress + mbi.RegionSize;
    }
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
            HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
            ScanMemory(hProc);
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
