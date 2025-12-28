#include <windows.h>
#include <stdio.h>

int main(void)
{
    HANDLE hToken = NULL;

    // Open the access token of the current process
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        printf("OpenProcessToken failed. Error: %lu\n", GetLastError());
        return 1;
    }

    printf("Process token opened successfully!\n");

    // Always close handles
    CloseHandle(hToken);

    return 0;
}
