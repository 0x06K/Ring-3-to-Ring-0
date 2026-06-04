#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef struct _RTL_MEMORY_ZONE {
    PVOID Segment;
    SIZE_T TotalSize;
    PVOID FirstBlock;
} RTL_MEMORY_ZONE, *PRTL_MEMORY_ZONE;

typedef NTSTATUS (WINAPI *pRtlCreateMemoryZone)(
    PRTL_MEMORY_ZONE Zone,
    SIZE_T InitialSize,
    ULONG Flags
);

int main() {
    printf("=== RtlCreateMemoryZone ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlCreateMemoryZone RtlCreateMemoryZone = 
        (pRtlCreateMemoryZone)GetProcAddress(ntdll, "RtlCreateMemoryZone");
    
    RTL_MEMORY_ZONE zone = {0};
    SIZE_T initialSize = 4096;
    
    NTSTATUS status = RtlCreateMemoryZone(&zone, initialSize, 0);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Zone Address: 0x%p\n", &zone);
    printf("Initial Size: %zu\n", initialSize);
    printf("Segment: 0x%p\n", zone.Segment);
    printf("Total Size: %zu\n", zone.TotalSize);
    printf("First Block: 0x%p\n", zone.FirstBlock);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}