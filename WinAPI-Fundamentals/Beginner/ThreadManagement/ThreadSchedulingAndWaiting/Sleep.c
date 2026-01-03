#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== Sleep ===\n");

    Sleep(1000);

    printf("Return Value: void\n");
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
