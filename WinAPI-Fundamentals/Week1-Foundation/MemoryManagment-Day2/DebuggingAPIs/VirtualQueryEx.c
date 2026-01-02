#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualQueryEx ===\n");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    MEMORY_BASIC_INFORMATION mbi;
    
    SIZE_T result = VirtualQueryEx(GetCurrentProcess(), addr, &mbi, sizeof(mbi));
    
    printf("Return Value: %zu\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Address: 0x%p\n", addr);
    printf("BaseAddress: 0x%p\n", mbi.BaseAddress);
    printf("AllocationBase: 0x%p\n", mbi.AllocationBase);
    printf("AllocationProtect: 0x%08lx\n", mbi.AllocationProtect);
    printf("RegionSize: %zu\n", mbi.RegionSize);
    printf("State: 0x%08lx\n", mbi.State);
    printf("Protect: 0x%08lx\n", mbi.Protect);
    printf("Type: 0x%08lx\n", mbi.Type);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}