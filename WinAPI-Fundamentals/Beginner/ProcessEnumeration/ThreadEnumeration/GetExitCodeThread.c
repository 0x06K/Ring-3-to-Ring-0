#include <windows.h>
#include <stdio.h>

int main(void)
{
    HANDLE hThread = GetCurrentThread();
    DWORD exitCode;

    if (GetExitCodeThread(hThread, &exitCode)) {
        printf("Thread exit code: %lu\n", exitCode);
    } else {
        printf("GetExitCodeThread failed\n");
    }

    return 0;
}
