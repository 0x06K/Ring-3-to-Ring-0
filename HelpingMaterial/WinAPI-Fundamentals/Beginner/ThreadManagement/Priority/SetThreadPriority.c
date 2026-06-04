#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== SetThreadPriority ===\n");

    BOOL ret = SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);

    printf("Return Value (BOOL): %d\n", ret);
    printf("Handle: 0x%p\n", GetCurrentThread());
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
