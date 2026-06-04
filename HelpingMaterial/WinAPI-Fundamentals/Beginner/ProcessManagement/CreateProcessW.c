#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== CreateProcessW ===\n");
    
    STARTUPINFOW si = {0};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = {0};
    
    BOOL result = CreateProcessW(L"C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, 
                                 FALSE, 0, NULL, NULL, &si, &pi);
    
    printf("Return Value: %d\n", result);
    printf("Application Name: C:\\Windows\\System32\\notepad.exe\n");
    printf("Process Handle: 0x%p\n", pi.hProcess);
    printf("Thread Handle: 0x%p\n", pi.hThread);
    printf("Process ID: %lu\n", pi.dwProcessId);
    printf("Thread ID: %lu\n", pi.dwThreadId);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}