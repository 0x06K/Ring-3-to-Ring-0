#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtProtectVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID *BaseAddress,
    PSIZE_T RegionSize,
    ULONG NewProtect,
    PULONG OldProtect
);

int main() {
    printf("=== NtProtectVirtualMemory ===\n");
    
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    pNtProtectVirtualMemory NtProtectVirtualMemory = (pNtProtectVirtualMemory)GetProcAddress(ntdll, "NtProtectVirtualMemory");
    
    PVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    SIZE_T size = 4096;
    ULONG oldProtect;
    NTSTATUS status = NtProtectVirtualMemory(GetCurrentProcess(), &addr, &size, PAGE_EXECUTE_READWRITE, &oldProtect);
    
    printf("NTSTATUS: 0x%08X\n", status);
    printf("Base Address: 0x%p\n", addr);
    printf("Region Size: %zu\n", size);
    printf("New Protection: PAGE_EXECUTE_READWRITE\n");
    printf("Old Protection: 0x%lX\n", oldProtect);
    
    return 0;
}