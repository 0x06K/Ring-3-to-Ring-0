#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef struct _RTL_MEMORY_ZONE {
    PVOID Segment;
    SIZE_T TotalSize;
    PVOID FirstBlock;
} RTL_MEMORY_ZONE, *PRTL_MEMORY_ZONE;

typedef NTSTATUS (WINAPI *pRtlCreateMemoryZone)(PRTL_MEMORY_ZONE, SIZE_T, ULONG);
typedef NTSTATUS (WINAPI *pRtlResetMemoryZone)(PRTL_MEMORY_ZONE);

int main() {
    printf("=== RtlResetMemoryZone ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlCreateMemoryZone RtlCreateMemoryZone = 
        (pRtlCreateMemoryZone)GetProcAddress(ntdll, "RtlCreateMemoryZone");
    pRtlResetMemoryZone RtlResetMemoryZone = 
        (pRtlResetMemoryZone)GetProcAddress(ntdll, "RtlResetMemoryZone");
    
    RTL_MEMORY_ZONE zone = {0};
    RtlCreateMemoryZone(&zone, 4096, 0);
    
    NTSTATUS status = RtlResetMemoryZone(&zone);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Zone Address: 0x%p\n", &zone);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}