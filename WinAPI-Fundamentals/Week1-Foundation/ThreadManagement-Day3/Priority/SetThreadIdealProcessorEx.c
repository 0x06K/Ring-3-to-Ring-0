#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== SetThreadIdealProcessorEx ===\n");

    PROCESSOR_NUMBER pn = {0};
    PROCESSOR_NUMBER prev = {0};

    BOOL ret = SetThreadIdealProcessorEx(GetCurrentThread(), &pn, &prev);

    printf("Return Value (BOOL): %d\n", ret);
    printf("Prev Group: %u\n", prev.Group);
    printf("Prev Number: %u\n", prev.Number);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
