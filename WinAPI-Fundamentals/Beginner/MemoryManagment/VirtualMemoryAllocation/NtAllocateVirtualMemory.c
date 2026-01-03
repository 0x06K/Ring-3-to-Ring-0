#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtAllocateVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID *BaseAddress,
    ULONG_PTR ZeroBits,
    PSIZE_T RegionSize,
    ULONG AllocationType,
    ULONG Protect
);

int main() {
    printf("=== NtAllocateVirtualMemory ===\n");
    
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    pNtAllocateVirtualMemory NtAllocateVirtualMemory = 
        (pNtAllocateVirtualMemory)GetProcAddress(ntdll, "NtAllocateVirtualMemory");
    
    PVOID baseAddr = NULL;
    SIZE_T size = 4096;
    NTSTATUS status = NtAllocateVirtualMemory(GetCurrentProcess(), &baseAddr, 0, &size, 
                                               MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    printf("NTSTATUS: 0x%08X\n", status);
    printf("Base Address: 0x%p\n", baseAddr);
    printf("Region Size: %zu\n", size);
    
    return 0;
}