#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== GetThreadPriority ===\n");

    int pr = GetThreadPriority(GetCurrentThread());

    printf("Priority: %d\n", pr);
    printf("Handle: 0x%p\n", GetCurrentThread());
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
