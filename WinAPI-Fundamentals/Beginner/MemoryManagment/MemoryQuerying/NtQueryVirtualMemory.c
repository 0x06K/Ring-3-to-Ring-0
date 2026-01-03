#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtQueryVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID BaseAddress,
    DWORD MemoryInformationClass,
    PVOID MemoryInformation,
    SIZE_T MemoryInformationLength,
    PSIZE_T ReturnLength
);

int main() {
    printf("=== NtQueryVirtualMemory ===\n");
    
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    pNtQueryVirtualMemory NtQueryVirtualMemory = (pNtQueryVirtualMemory)GetProcAddress(ntdll, "NtQueryVirtualMemory");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    MEMORY_BASIC_INFORMATION mbi;
    SIZE_T returnLength;
    NTSTATUS status = NtQueryVirtualMemory(GetCurrentProcess(), addr, 0, &mbi, sizeof(mbi), &returnLength);
    
    printf("NTSTATUS: 0x%08X\n", status);
    printf("Return Length: %zu\n", returnLength);
    printf("Base Address: 0x%p\n", mbi.BaseAddress);
    printf("Allocation Base: 0x%p\n", mbi.AllocationBase);
    printf("Allocation Protect: 0x%lX\n", mbi.AllocationProtect);
    printf("Region Size: %zu\n", mbi.RegionSize);
    printf("State: 0x%lX\n", mbi.State);
    printf("Protect: 0x%lX\n", mbi.Protect);
    printf("Type: 0x%lX\n", mbi.Type);
    
    return 0;
}