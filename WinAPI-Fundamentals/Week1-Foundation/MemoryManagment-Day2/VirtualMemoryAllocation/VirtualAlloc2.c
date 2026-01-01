#include <windows.h>
#include <stdio.h>

typedef PVOID (WINAPI *pVirtualAlloc2)(
    HANDLE Process,
    PVOID BaseAddress,
    SIZE_T Size,
    ULONG AllocationType,
    ULONG PageProtection,
    MEM_EXTENDED_PARAMETER* ExtendedParameters,
    ULONG ParameterCount
);

int main() {
    printf("=== VirtualAlloc2 ===\n");
    
    HMODULE kernelbase = LoadLibraryA("kernelbase.dll");
    pVirtualAlloc2 VirtualAlloc2 = (pVirtualAlloc2)GetProcAddress(kernelbase, "VirtualAlloc2");
    
    if (VirtualAlloc2 == NULL) {
        printf("VirtualAlloc2 not available (Windows 10+ required)\n");
        printf("Error Code: %lu\n", GetLastError());
        return 1;
    }
    
    LPVOID addr = VirtualAlloc2(GetCurrentProcess(), NULL, 4096, 
                                 MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE, NULL, 0);
    
    printf("Return Address: 0x%p\n", addr);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}