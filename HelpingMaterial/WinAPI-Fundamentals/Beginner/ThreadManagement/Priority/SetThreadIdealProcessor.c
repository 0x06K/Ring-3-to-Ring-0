#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== SetThreadIdealProcessor ===\n");

    DWORD prev = SetThreadIdealProcessor(GetCurrentThread(), 0);

    printf("Previous Processor: %lu\n", prev);
    printf("Handle: 0x%p\n", GetCurrentThread());
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
