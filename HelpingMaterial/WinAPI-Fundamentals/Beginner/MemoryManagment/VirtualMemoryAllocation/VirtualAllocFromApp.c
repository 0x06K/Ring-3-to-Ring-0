#include <windows.h>
#include <stdio.h>

typedef PVOID (WINAPI *pVirtualAllocFromApp)(
    PVOID BaseAddress,
    SIZE_T Size,
    ULONG AllocationType,
    ULONG Protection
);

int main() {
    printf("=== VirtualAllocFromApp ===\n");
    
    HMODULE kernelbase = LoadLibraryA("kernelbase.dll");
    if (!kernelbase) {
        printf("Failed to load kernelbase.dll\n");
        return 1;
    }
    
    pVirtualAllocFromApp func = (pVirtualAllocFromApp)GetProcAddress(kernelbase, "VirtualAllocFromApp");
    
    if (func == NULL) {
        printf("VirtualAllocFromApp not available\n");
        printf("Error Code: %lu\n", GetLastError());
        return 1;
    }
    
    LPVOID addr = func(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    printf("Return Address: 0x%p\n", addr);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}