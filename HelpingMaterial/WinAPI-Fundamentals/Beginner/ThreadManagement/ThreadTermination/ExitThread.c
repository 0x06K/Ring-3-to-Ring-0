#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== ExitThread ===\n");

    ExitThread(0x1234);

    printf("Return Value: void (no return)\n");
    printf("Exit Code: 0x1234\n");
    printf("Error Code: %lu\n", GetLastError());

    return 0;
}
