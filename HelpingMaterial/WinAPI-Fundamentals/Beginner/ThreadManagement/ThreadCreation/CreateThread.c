#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    return 0;
}

int main() {
    printf("=== CreateThread ===\n");
    
    DWORD threadId;
    
    HANDLE result = CreateThread(NULL, 0, ThreadProc, NULL, 0, &threadId);
    
    printf("Return Handle: 0x%p\n", result);
    printf("Thread ID: %lu\n", threadId);
    printf("Stack Size: %lu\n", 0);
    printf("Thread Function: 0x%p\n", ThreadProc);
    printf("Parameter: 0x%p\n", (LPVOID)NULL);
    printf("Creation Flags: %lu\n", 0);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}