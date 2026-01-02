#include <windows.h>
#include <stdio.h>

typedef PVOID (WINAPI *pRegisterBadMemoryNotification)(PVOID);
typedef BOOL (WINAPI *pUnregisterBadMemoryNotification)(PVOID);

void CALLBACK BadMemoryCallback(void* context) {
    printf("Bad memory detected!\n");
}

int main() {
    printf("=== UnregisterBadMemoryNotification ===\n");
    
    HMODULE kernel32 = LoadLibraryA("kernel32.dll");
    pRegisterBadMemoryNotification RegisterBadMemoryNotification = 
        (pRegisterBadMemoryNotification)GetProcAddress(kernel32, "RegisterBadMemoryNotification");
    pUnregisterBadMemoryNotification UnregisterBadMemoryNotification = 
        (pUnregisterBadMemoryNotification)GetProcAddress(kernel32, "UnregisterBadMemoryNotification");
    
    PVOID registrationHandle = RegisterBadMemoryNotification((PVOID)BadMemoryCallback);
    
    BOOL result = UnregisterBadMemoryNotification(registrationHandle);
    
    printf("Return Value: %d\n", result);
    printf("Registration Handle: 0x%p\n", registrationHandle);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}