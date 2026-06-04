#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== SetThreadAffinityMask ===\n");

    DWORD_PTR mask = SetThreadAffinityMask(GetCurrentThread(), 1);

    printf("Previous Mask: 0x%p\n", (void*)mask);
    printf("Handle: 0x%p\n", GetCurrentThread());
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
