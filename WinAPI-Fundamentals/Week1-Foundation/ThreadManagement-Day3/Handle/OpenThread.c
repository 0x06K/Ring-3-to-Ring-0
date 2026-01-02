#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== OpenThread ===\n");

    HANDLE h = OpenThread(THREAD_ALL_ACCESS, FALSE, GetCurrentThreadId());

    printf("Handle: 0x%p\n", h);
    printf("Thread ID: %lu\n", GetCurrentThreadId());
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
