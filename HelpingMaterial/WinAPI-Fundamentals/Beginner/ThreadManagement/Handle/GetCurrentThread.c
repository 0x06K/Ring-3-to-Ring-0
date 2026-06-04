#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetCurrentThread ===\n");

    HANDLE h = GetCurrentThread();

    printf("Handle: 0x%p\n", h);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
