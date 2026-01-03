#include <windows.h>
#include <stdio.h>

typedef BOOL (WINAPI *pVirtualProtectFromApp)(
    PVOID Address,
    SIZE_T Size,
    ULONG NewProtection,
    PULONG OldProtection
);

int main() {
    printf("=== VirtualProtectFromApp ===\n");
    
    HMODULE kernelbase = LoadLibraryA("kernelbase.dll");
    pVirtualProtectFromApp func = (pVirtualProtectFromApp)GetProcAddress(kernelbase, "VirtualProtectFromApp");
    
    if (func == NULL) {
        printf("VirtualProtectFromApp not available\n");
        printf("Error Code: %lu\n", GetLastError());
        return 1;
    }
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    DWORD oldProtect;
    BOOL result = func(addr, 4096, PAGE_EXECUTE_READ, &oldProtect);
    
    printf("Address: 0x%p\n", addr);
    printf("New Protection: PAGE_EXECUTE_READ\n");
    printf("Old Protection: 0x%lX\n", oldProtect);
    printf("Return Value: %d\n", result);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}