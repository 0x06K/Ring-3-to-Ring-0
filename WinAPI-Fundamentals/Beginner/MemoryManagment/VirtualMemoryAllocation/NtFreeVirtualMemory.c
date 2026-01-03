#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtFreeVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID *BaseAddress,
    PSIZE_T RegionSize,
    ULONG FreeType
);

int main() {
    printf("=== NtFreeVirtualMemory ===\n");
    
    PVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    pNtFreeVirtualMemory NtFreeVirtualMemory = 
        (pNtFreeVirtualMemory)GetProcAddress(ntdll, "NtFreeVirtualMemory");
    
    SIZE_T size = 0;
    NTSTATUS status = NtFreeVirtualMemory(GetCurrentProcess(), &addr, &size, MEM_RELEASE);
    
    printf("NTSTATUS: 0x%08X\n", status);
    printf("Base Address: 0x%p\n", addr);
    printf("Region Size: %zu\n", size);
    
    return 0;
}