#include <windows.h>
#include <stdio.h>

int main(void)
{
    WCHAR imagePath[MAX_PATH];
    DWORD size = MAX_PATH;
    
    // GetCurrentProcess() gives the handling to the current process
    if (QueryFullProcessImageNameW(GetCurrentProcess(), 0, imagePath, &size)) {
        wprintf(L"Process Image Path: %s\n", imagePath);
    }
    else
    {
        wprintf(L"QueryFullProcessImageName failed. Error: %lu\n", GetLastError());
    }

    return 0;
}
