#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    return 0;
}

int main() {
    printf("=== CreateRemoteThread ===\n");
    
    DWORD threadId;
    
    HANDLE result = CreateRemoteThread(GetCurrentProcess(), NULL, 0, 
                                       (LPTHREAD_START_ROUTINE)ThreadProc, NULL, 0, &threadId);
    
    printf("Return Handle: 0x%p\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Thread ID: %lu\n", threadId);
    printf("Stack Size: %lu\n", 0);
    printf("Start Address: 0x%p\n", ThreadProc);
    printf("Parameter: 0x%p\n", (LPVOID)NULL);
    printf("Creation Flags: %lu\n", 0);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}