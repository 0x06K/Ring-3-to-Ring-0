#include <windows.h>
#include <stdio.h>
#include <sddl.h>   // For ConvertSidToStringSid

int main(void)
{
    HANDLE hToken = NULL;

    // Open the current process token
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        printf("OpenProcessToken failed: %lu\n", GetLastError());
        return 1;
    }

    DWORD size = 0;

    // First call to get required buffer size
    GetTokenInformation(
        hToken,
        TokenUser,
        NULL,
        0,
        &size
    );

    PTOKEN_USER tokenUser = (PTOKEN_USER)malloc(size);
    if (!tokenUser) {
        CloseHandle(hToken);
        return 1;
    }

    // Actual query
    if (!GetTokenInformation(
            hToken,
            TokenUser,
            tokenUser,
            size,
            &size))
    {
        printf("GetTokenInformation failed: %lu\n", GetLastError());
        free(tokenUser);
        CloseHandle(hToken);
        return 1;
    }

    // Convert SID to string
    LPWSTR sidString = NULL;
    if (ConvertSidToStringSidW(tokenUser->User.Sid, &sidString)) {
        wprintf(L"User SID: %s\n", sidString);
        LocalFree(sidString);
    }

    free(tokenUser);
    CloseHandle(hToken);
    return 0;
}
