#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef NTSTATUS (WINAPI *pNtAllocateVirtualMemoryEx)(
    HANDLE ProcessHandle,
    PVOID *BaseAddress,
    PSIZE_T RegionSize,
    ULONG AllocationType,
    ULONG PageProtection,
    PVOID ExtendedParameters,
    ULONG ExtendedParameterCount
);

int main() {
    printf("=== NtAllocateVirtualMemoryEx ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtAllocateVirtualMemoryEx NtAllocateVirtualMemoryEx = 
        (pNtAllocateVirtualMemoryEx)GetProcAddress(ntdll, "NtAllocateVirtualMemoryEx");
    
    PVOID baseAddress = NULL;
    SIZE_T regionSize = 4096;
    
    NTSTATUS status = NtAllocateVirtualMemoryEx(GetCurrentProcess(), &baseAddress, &regionSize,
                                                MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE, NULL, 0);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Base Address: 0x%p\n", baseAddress);
    printf("Region Size: %zu\n", regionSize);
    printf("Allocation Type: MEM_COMMIT | MEM_RESERVE\n");
    printf("Page Protection: PAGE_READWRITE\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}