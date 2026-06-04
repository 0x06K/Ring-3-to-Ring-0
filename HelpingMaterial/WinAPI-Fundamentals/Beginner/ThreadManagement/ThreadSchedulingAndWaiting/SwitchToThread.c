#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== SwitchToThread ===\n");

    BOOL ret = SwitchToThread();

    printf("Return Value (BOOL): %d\n", ret);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
