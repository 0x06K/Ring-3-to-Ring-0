#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== WaitForSingleObject ===\n");

    DWORD ret = WaitForSingleObject(GetCurrentThread(), 1000);

    printf("Return Value (DWORD): %lu\n", ret);
    printf("Handle: 0x%p\n", GetCurrentThread());
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
