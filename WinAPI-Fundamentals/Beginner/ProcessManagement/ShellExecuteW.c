#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== ShellExecuteW ===\n");
    
    HINSTANCE result = ShellExecuteW(NULL, L"open", L"notepad.exe", NULL, NULL, SW_SHOW);
    
    printf("Return Value: 0x%p\n", result);
    printf("HWND: 0x%p\n", (HWND)NULL);
    printf("Operation: open\n");
    printf("File: notepad.exe\n");
    printf("Parameters: (null)\n");
    printf("Directory: (null)\n");
    printf("Show Command: SW_SHOW (%d)\n", SW_SHOW);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}