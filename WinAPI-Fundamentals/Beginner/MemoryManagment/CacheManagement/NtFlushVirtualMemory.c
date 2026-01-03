#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef struct _IO_STATUS_BLOCK {
    union {
        NTSTATUS Status;
        PVOID Pointer;
    };
    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef NTSTATUS (WINAPI *pNtFlushVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID *BaseAddress,
    PSIZE_T RegionSize,
    PIO_STATUS_BLOCK IoStatus
);

int main() {
    printf("=== NtFlushVirtualMemory ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtFlushVirtualMemory NtFlushVirtualMemory = (pNtFlushVirtualMemory)GetProcAddress(ntdll, "NtFlushVirtualMemory");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    PVOID baseAddr = addr;
    SIZE_T regionSize = 4096;
    IO_STATUS_BLOCK ioStatus;
    
    NTSTATUS status = NtFlushVirtualMemory(GetCurrentProcess(), &baseAddr, &regionSize, &ioStatus);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Base Address: 0x%p\n", baseAddr);
    printf("Region Size: %zu\n", regionSize);
    printf("IO Status: 0x%08lx\n", ioStatus.Status);
    printf("IO Information: %llu\n", ioStatus.Information);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}