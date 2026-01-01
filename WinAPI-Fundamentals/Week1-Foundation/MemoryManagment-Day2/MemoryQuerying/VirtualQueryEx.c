#include <windows.h>
#include <stdio.h>

int main() {
    printf("=== VirtualQueryEx ===\n");
    
    HANDLE hProcess = GetCurrentProcess();
    LPVOID addr = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    MEMORY_BASIC_INFORMATION mbi;
    SIZE_T result = VirtualQueryEx(hProcess, addr, &mbi, sizeof(mbi));
    
    printf("Process Handle: 0x%p\n", hProcess);
    printf("Return Value: %zu bytes\n", result);
    printf("Base Address: 0x%p\n", mbi.BaseAddress);
    printf("Allocation Base: 0x%p\n", mbi.AllocationBase);
    printf("Allocation Protect: 0x%lX\n", mbi.AllocationProtect);
    printf("Region Size: %zu\n", mbi.RegionSize);
    printf("State: 0x%lX\n", mbi.State);
    printf("Protect: 0x%lX\n", mbi.Protect);
    printf("Type: 0x%lX\n", mbi.Type);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}