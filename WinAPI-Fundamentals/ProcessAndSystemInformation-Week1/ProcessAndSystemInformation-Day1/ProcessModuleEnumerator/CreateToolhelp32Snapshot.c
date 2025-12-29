#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include "colors.h"

#define REPEAT(c, n) do { for(int i=0;i<(n);i++) putchar(c); printf("\n");} while(0)

int main(void)
{
    DWORD pid = GetCurrentProcessId();

    printf(CLR_BOLD CLR_CYAN "[+] Enumerating modules for PID: %lu\n\n" CLR_RESET, pid);
    REPEAT('+',89);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32,
        pid
    );

    if (hSnapshot == INVALID_HANDLE_VALUE) {
        printf(CLR_RED "[-] CreateToolhelp32Snapshot failed (%lu)\n" CLR_RESET, GetLastError());
        return 1;
    }

    MODULEENTRY32 me;
    me.dwSize = sizeof(MODULEENTRY32);

    if (!Module32First(hSnapshot, &me)) {
        printf(CLR_RED "[-] Module32First failed (%lu)\n" CLR_RESET, GetLastError());
        CloseHandle(hSnapshot);
        return 1;
    }
    printf(CLR_GREEN "|| %-30s || Base  %-16s  || Size: " CLR_RESET "%-16s ||\n", "Module", " ",  " ");
    do {

        printf(CLR_GREEN "|| " CLR_RESET CLR_YELLOW "%-30s " CLR_RESET CLR_BLUE "|| Base: " CLR_RESET "%p  " CLR_MAGENTA "|| Size: " CLR_RESET "%-10lu bytes ||\n", me.szModule, me.modBaseAddr,  me.modBaseSize);

    } while (Module32Next(hSnapshot, &me));

    CloseHandle(hSnapshot);
    


    printf("\n" CLR_GREEN "[+] Enumeration complete.\n" CLR_RESET);
    return 0;
}
