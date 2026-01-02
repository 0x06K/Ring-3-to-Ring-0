#include <windows.h>
#include <stdio.h>

typedef PVOID (WINAPI *pRegisterBadMemoryNotification)(PVOID Callback);

void CALLBACK BadMemoryCallback(void* context) {
    printf("Bad memory detected!\n");
}

int main() {
    printf("=== RegisterBadMemoryNotification ===\n");
    
    HMODULE kernel32 = LoadLibraryA("kernel32.dll");
    pRegisterBadMemoryNotification RegisterBadMemoryNotification = 
        (pRegisterBadMemoryNotification)GetProcAddress(kernel32, "RegisterBadMemoryNotification");
    
    PVOID result = RegisterBadMemoryNotification((PVOID)BadMemoryCallback);
    
    printf("Return Handle: 0x%p\n", result);
    printf("Callback Address: 0x%p\n", (PVOID)BadMemoryCallback);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}