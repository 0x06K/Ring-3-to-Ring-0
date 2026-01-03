#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef NTSTATUS (WINAPI *pNtLockVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID *BaseAddress,
    PSIZE_T RegionSize,
    ULONG MapType
);

int main() {
    printf("=== NtLockVirtualMemory ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtLockVirtualMemory NtLockVirtualMemory = (pNtLockVirtualMemory)GetProcAddress(ntdll, "NtLockVirtualMemory");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    PVOID baseAddr = addr;
    SIZE_T regionSize = 4096;
    
    NTSTATUS status = NtLockVirtualMemory(GetCurrentProcess(), &baseAddr, &regionSize, 1);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Base Address: 0x%p\n", baseAddr);
    printf("Region Size: %zu\n", regionSize);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}