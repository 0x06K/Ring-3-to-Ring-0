#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef struct _RTL_MEMORY_BLOCK_LOOKASIDE {
    BYTE Reserved[128];
} RTL_MEMORY_BLOCK_LOOKASIDE, *PRTL_MEMORY_BLOCK_LOOKASIDE;

typedef NTSTATUS (WINAPI *pRtlCreateMemoryBlockLookaside)(
    PRTL_MEMORY_BLOCK_LOOKASIDE Lookaside,
    ULONG Flags,
    ULONG BlockSize,
    ULONG Depth
);

int main() {
    printf("=== RtlCreateMemoryBlockLookaside ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlCreateMemoryBlockLookaside RtlCreateMemoryBlockLookaside = 
        (pRtlCreateMemoryBlockLookaside)GetProcAddress(ntdll, "RtlCreateMemoryBlockLookaside");
    
    RTL_MEMORY_BLOCK_LOOKASIDE lookaside = {0};
    ULONG blockSize = 64;
    ULONG depth = 16;
    
    NTSTATUS status = RtlCreateMemoryBlockLookaside(&lookaside, 0, blockSize, depth);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Lookaside Address: 0x%p\n", &lookaside);
    printf("Block Size: %lu\n", blockSize);
    printf("Depth: %lu\n", depth);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}