#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    return 0;
}

int main() {
    printf("=== CreateRemoteThreadEx ===\n");
    
    DWORD threadId;
    
    HANDLE result = CreateRemoteThreadEx(GetCurrentProcess(), NULL, 0, 
                                         (LPTHREAD_START_ROUTINE)ThreadProc, NULL, 
                                         0, NULL, &threadId);
    
    printf("Return Handle: 0x%p\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Thread ID: %lu\n", threadId);
    printf("Stack Size: %zu\n", (SIZE_T)0);
    printf("Start Address: 0x%p\n", ThreadProc);
    printf("Parameter: 0x%p\n", (LPVOID)NULL);
    printf("Creation Flags: %lu\n", 0);
    printf("Attribute List: 0x%p\n", (LPPROC_THREAD_ATTRIBUTE_LIST)NULL);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}