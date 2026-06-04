#include <windows.h>
#include <stdio.h>
#include <psapi.h>

int main() {
    printf("=== QueryWorkingSetEx ===\n");
    
    PSAPI_WORKING_SET_EX_INFORMATION wsInfo;
    wsInfo.VirtualAddress = GetModuleHandle(NULL);
    
    BOOL result = QueryWorkingSetEx(GetCurrentProcess(), &wsInfo, sizeof(wsInfo));
    
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    printf("Virtual Address: 0x%p\n", wsInfo.VirtualAddress);
    printf("Valid: %llu\n", wsInfo.VirtualAttributes.Valid);
    printf("ShareCount: %llu\n", wsInfo.VirtualAttributes.ShareCount);
    printf("Win32Protection: %llu\n", wsInfo.VirtualAttributes.Win32Protection);
    
    return 0;
}