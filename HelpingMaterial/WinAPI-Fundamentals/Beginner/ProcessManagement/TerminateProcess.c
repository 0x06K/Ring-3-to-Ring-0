#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== TerminateProcess ===\n");
    
    STARTUPINFOA si = {0};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = {0};
    
    CreateProcessA("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, 
                   FALSE, 0, NULL, NULL, &si, &pi);
    
    Sleep(100);
    
    BOOL result = TerminateProcess(pi.hProcess, 99);
    
    printf("Return Value: %d\n", result);
    printf("Process Handle: 0x%p\n", pi.hProcess);
    printf("Exit Code: %u\n", 99);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}