#include <windows.h>
#include <stdio.h>

int main(void)
{
    HANDLE hThread = GetCurrentThread();
    DWORD tid = GetThreadId(hThread);

    printf("Thread ID: %lu\n", tid);
    return 0;
}
