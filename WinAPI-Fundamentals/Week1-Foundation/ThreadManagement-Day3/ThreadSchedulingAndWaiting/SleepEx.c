#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== SleepEx ===\n");

    DWORD ret = SleepEx(1000, TRUE);

    printf("Return Value (DWORD): %lu\n", ret);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
