#include <windows.h>
#include <stdio.h>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    DWORD pid = 0;

    // Get the process ID for this window
    GetWindowThreadProcessId(hwnd, &pid);

    // Get the window title
    WCHAR title[256];
    GetWindowTextW(hwnd, title, sizeof(title)/sizeof(WCHAR));

    // Only print visible windows with non-empty titles
    if (IsWindowVisible(hwnd) && wcslen(title) > 0)
    {
        wprintf(L"Window: \"%s\"  PID: %lu\n", title, pid);
    }

    return TRUE; // Continue enumeration
}

int main(void)
{
    // Enumerate all top-level windows
    EnumWindows(EnumWindowsProc, 0);

    return 0;
}
