#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualProtectEx ===\n");
    
    HANDLE hProcess = GetCurrentProcess();
    LPVOID addr = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    DWORD oldProtect;
    BOOL result = VirtualProtectEx(hProcess, addr, 4096, PAGE_READONLY, &oldProtect);
    
    printf("Process Handle: 0x%p\n", hProcess);
    printf("Address: 0x%p\n", addr);
    printf("New Protection: PAGE_READONLY\n");
    printf("Old Protection: 0x%lX\n", oldProtect);
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}