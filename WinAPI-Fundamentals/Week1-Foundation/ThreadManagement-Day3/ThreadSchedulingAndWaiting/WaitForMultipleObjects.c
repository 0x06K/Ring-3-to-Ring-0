#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== WaitForMultipleObjects ===\n");

    HANDLE h[1] = { GetCurrentThread() };
    DWORD ret = WaitForMultipleObjects(1, h, FALSE, 1000);

    printf("Return Value (DWORD): %lu\n", ret);
    printf("Handle[0]: 0x%p\n", h[0]);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
