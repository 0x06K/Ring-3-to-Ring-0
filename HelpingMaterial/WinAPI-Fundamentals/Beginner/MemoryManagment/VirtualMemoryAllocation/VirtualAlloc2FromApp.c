#include <windows.h>
#include <stdio.h>

typedef PVOID (WINAPI *pVirtualAlloc2FromApp)(
    HANDLE Process,
    PVOID BaseAddress,
    SIZE_T Size,
    ULONG AllocationType,
    ULONG PageProtection,
    void* ExtendedParameters,
    ULONG ParameterCount
);

int main() {
    printf("=== VirtualAlloc2FromApp ===\n");
    
    HMODULE kernelbase = LoadLibraryA("kernelbase.dll");
    if (!kernelbase) {
        printf("Failed to load kernelbase.dll\n");
        return 1;
    }
    
    pVirtualAlloc2FromApp func = (pVirtualAlloc2FromApp)GetProcAddress(kernelbase, "VirtualAlloc2FromApp");
    
    if (func == NULL) {
        printf("VirtualAlloc2FromApp not available\n");
        printf("Error Code: %lu\n", GetLastError());
        return 1;
    }
    
    LPVOID addr = func(GetCurrentProcess(), NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE, NULL, 0);
    
    printf("Return Address: 0x%p\n", addr);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}