#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== TerminateThread ===\n");

    BOOL ret = TerminateThread(GetCurrentThread(), 0xDEAD);

    printf("Return Value (BOOL): %d\n", ret);
    printf("Thread Handle: 0x%p\n", GetCurrentThread());
    printf("Exit Code: 0xDEAD\n");
    printf("Error Code: %lu\n", GetLastError());

    return 0;
}
