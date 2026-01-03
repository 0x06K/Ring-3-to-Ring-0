#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== DuplicateHandle ===\n");

    HANDLE dup = NULL;

    BOOL ret = DuplicateHandle(
        GetCurrentProcess(),
        GetCurrentThread(),
        GetCurrentProcess(),
        &dup,
        0,
        FALSE,
        DUPLICATE_SAME_ACCESS
    );

    printf("Return Value (BOOL): %d\n", ret);
    printf("Original Handle: 0x%p\n", GetCurrentThread());
    printf("Duplicated Handle: 0x%p\n", dup);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
