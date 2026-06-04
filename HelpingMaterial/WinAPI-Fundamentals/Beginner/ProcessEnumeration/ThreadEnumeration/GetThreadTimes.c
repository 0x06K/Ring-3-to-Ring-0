#include <windows.h>
#include <stdio.h>

double FileTimeToSeconds(FILETIME ft) {
    ULONGLONG time = (((ULONGLONG)ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
    return time / 10000000.0; // 100-ns units to seconds
}

int main(void)
{
    FILETIME creation, exit, kernel, user;

    if (GetThreadTimes(GetCurrentThread(), &creation, &exit, &kernel, &user)) {
        printf("Kernel time: %.6f sec\n", FileTimeToSeconds(kernel));
        printf("User time  : %.6f sec\n", FileTimeToSeconds(user));
        printf("Creation time: %.6f sec since FILETIME epoch\n", FileTimeToSeconds(creation));
        printf("Exit time    : %.6f sec since FILETIME epoch\n", FileTimeToSeconds(exit));
    } else {
        printf("GetThreadTimes failed\n");
    }

    return 0;
}
