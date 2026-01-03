#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetCurrentThreadId ===\n");

    DWORD tid = GetCurrentThreadId();

    printf("Thread ID: %lu\n", tid);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
