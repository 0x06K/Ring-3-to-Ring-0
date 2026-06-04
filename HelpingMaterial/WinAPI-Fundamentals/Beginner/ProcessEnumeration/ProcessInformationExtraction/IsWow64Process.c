#include <windows.h>
#include <stdio.h>

int main(void)
{
    BOOL isWow64 = FALSE;

    if (!IsWow64Process(GetCurrentProcess(), &isWow64))
    {
        printf("IsWow64Process failed. Error: %lu\n", GetLastError());
        return 1;
    }

    if (isWow64)
        printf("Process is running under WOW64 (32-bit on 64-bit Windows).\n");
    else
        printf("Process is NOT running under WOW64 (native architecture).\n");

    return 0;
}
