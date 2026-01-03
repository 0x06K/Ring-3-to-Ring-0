#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== WinExec ===\n");
    
    UINT result = WinExec("notepad.exe", SW_SHOW);
    
    printf("Return Value: %u\n", result);
    printf("Command Line: notepad.exe\n");
    printf("Show Command: SW_SHOW (%d)\n", SW_SHOW);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}