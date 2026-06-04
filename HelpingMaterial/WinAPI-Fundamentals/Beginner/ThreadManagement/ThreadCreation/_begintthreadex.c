#include <windows.h>
#include <process.h>
#include <stdio.h>

unsigned __stdcall ThreadProc(void* param) {
    return 0;
}

int main() {
    printf("=== _beginthreadex ===\n");
    
    unsigned threadId;
    
    uintptr_t result = _beginthreadex(NULL, 0, ThreadProc, NULL, 0, &threadId);
    
    printf("Return Handle: 0x%p\n", (HANDLE)result);
    printf("Thread ID: %u\n", threadId);
    printf("Stack Size: %u\n", 0);
    printf("Thread Function: 0x%p\n", ThreadProc);
    printf("Parameter: 0x%p\n", (void*)NULL);
    printf("Init Flag: %u\n", 0);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}