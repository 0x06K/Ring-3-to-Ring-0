#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    Sleep(10000);
    return 0;
}

int main() {
    printf("=== Wow64SuspendThread ===\n");
    
    DWORD threadId;
    HANDLE thread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &threadId);
    
    DWORD result = Wow64SuspendThread(thread);
    
    printf("Return Value: %lu\n", result);
    printf("Thread Handle: 0x%p\n", thread);
    printf("Thread ID: %lu\n", threadId);
    printf("Previous Suspend Count: %lu\n", result);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}