#include <stdio.h>
#include "NtAllocateVirtualMemory.h"

extern DWORD regionSize;
extern void *baseAddress;
extern void* gadget;
extern uint64_t stacksize[7];
extern uint64_t *ret[7];
extern DWORD status;
void main()
{
    HMODULE hModule = GetModuleHandle("ntdll.dll");
    FARPROC ntHproc = GetProcAddress(hModule, "NtAllocateVirtualMemory");
    gadget = (void *)((uint8_t *)ntHproc);

    fillmyarray(ret, stacksize);

    HANDLE hThread = CreateThread(
        NULL,
        0x10000,
        SyscallThread,
        NULL,
        0,
        NULL);

    if (hThread == NULL)
    {
        printf("CreateThread failed: %lu\n", GetLastError());
        return;
    }

    WaitForSingleObject(hThread, INFINITE);
    if (status == 0)
    {
        printf("%d BYTES Allocated AT: %p\nStatus Code: %X\n", regionSize, baseAddress, status);
    }
    else
    {
        printf("Failed To Allocate Memory. Error Code: %X", status);
    }
    CloseHandle(hThread);
}
