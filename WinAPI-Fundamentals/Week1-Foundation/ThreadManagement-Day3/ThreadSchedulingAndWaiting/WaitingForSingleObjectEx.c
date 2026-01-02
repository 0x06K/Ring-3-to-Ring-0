#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== WaitForSingleObjectEx ===\n");

    DWORD ret = WaitForSingleObjectEx(GetCurrentThread(), 1000, TRUE);

    printf("Return Value (DWORD): %lu\n", ret);
    printf("Handle: 0x%p\n", GetCurrentThread());
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
