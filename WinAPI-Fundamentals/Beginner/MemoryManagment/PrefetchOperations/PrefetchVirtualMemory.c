#include <windows.h>
#include <stdio.h>

typedef struct _WIN32_MEMORY_RANGE_ENTRY {
    PVOID VirtualAddress;
    SIZE_T NumberOfBytes;
} WIN32_MEMORY_RANGE_ENTRY, *PWIN32_MEMORY_RANGE_ENTRY;

typedef BOOL (WINAPI *pPrefetchVirtualMemory)(
    HANDLE hProcess,
    ULONG_PTR NumberOfEntries,
    PWIN32_MEMORY_RANGE_ENTRY VirtualAddresses,
    ULONG Flags
);

int main() {
    printf("=== PrefetchVirtualMemory ===\n");
    
    HMODULE kernel32 = LoadLibraryA("kernel32.dll");
    pPrefetchVirtualMemory PrefetchVirtualMemory = (pPrefetchVirtualMemory)GetProcAddress(kernel32, "PrefetchVirtualMemory");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    WIN32_MEMORY_RANGE_ENTRY entry;
    entry.VirtualAddress = addr;
    entry.NumberOfBytes = 4096;
    
    BOOL result = PrefetchVirtualMemory(GetCurrentProcess(), 1, &entry, 0);
    
    printf("Return Value: %d\n", result);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Number of Entries: %llu\n", 1ULL);
    printf("Virtual Address: 0x%p\n", entry.VirtualAddress);
    printf("Number of Bytes: %zu\n", entry.NumberOfBytes);
    printf("Flags: %lu\n", 0UL);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}