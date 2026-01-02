#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== WaitForMultipleObjectsEx ===\n");

    HANDLE h[1] = { GetCurrentThread() };
    DWORD ret = WaitForMultipleObjectsEx(1, h, FALSE, 1000, TRUE);

    printf("Return Value (DWORD): %lu\n", ret);
    printf("Handle[0]: 0x%p\n", h[0]);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
