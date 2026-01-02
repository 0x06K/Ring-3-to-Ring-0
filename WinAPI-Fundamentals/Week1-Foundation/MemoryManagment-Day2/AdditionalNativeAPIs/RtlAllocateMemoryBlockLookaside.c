#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef struct _RTL_MEMORY_BLOCK_LOOKASIDE {
    BYTE Reserved[128];
} RTL_MEMORY_BLOCK_LOOKASIDE, *PRTL_MEMORY_BLOCK_LOOKASIDE;

typedef NTSTATUS (WINAPI *pRtlCreateMemoryBlockLookaside)(PRTL_MEMORY_BLOCK_LOOKASIDE, ULONG, ULONG, ULONG);
typedef PVOID (WINAPI *pRtlAllocateMemoryBlockLookaside)(PRTL_MEMORY_BLOCK_LOOKASIDE);

int main() {
    printf("=== RtlAllocateMemoryBlockLookaside ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlCreateMemoryBlockLookaside RtlCreateMemoryBlockLookaside = 
        (pRtlCreateMemoryBlockLookaside)GetProcAddress(ntdll, "RtlCreateMemoryBlockLookaside");
    pRtlAllocateMemoryBlockLookaside RtlAllocateMemoryBlockLookaside = 
        (pRtlAllocateMemoryBlockLookaside)GetProcAddress(ntdll, "RtlAllocateMemoryBlockLookaside");
    
    RTL_MEMORY_BLOCK_LOOKASIDE lookaside = {0};
    RtlCreateMemoryBlockLookaside(&lookaside, 0, 64, 16);
    
    PVOID result = RtlAllocateMemoryBlockLookaside(&lookaside);
    
    printf("Return Address: 0x%p\n", result);
    printf("Lookaside Address: 0x%p\n", &lookaside);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}