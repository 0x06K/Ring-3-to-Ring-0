#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

int main(void)
{
    DWORD pid = GetCurrentProcessId();
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return 1;

    THREADENTRY32 te;
    te.dwSize = sizeof(THREADENTRY32);

    if (Thread32First(snapshot, &te)) {
        do {
            if (te.th32OwnerProcessID == pid) {
                printf("Thread ID: %lu\n", te.th32ThreadID);
                printf("Base Priority: %ld\n", te.tpBasePri);
                printf("Delta Priority: %ld\n", te.tpDeltaPri);
                printf("Flags: %lu\n\n", te.dwFlags);
            }
        } while (Thread32Next(snapshot, &te));
    }

    CloseHandle(snapshot);
    return 0;
}
