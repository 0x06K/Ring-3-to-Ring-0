#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef struct _RTL_MEMORY_ZONE {
    PVOID Segment;
    SIZE_T TotalSize;
    PVOID FirstBlock;
} RTL_MEMORY_ZONE, *PRTL_MEMORY_ZONE;

typedef NTSTATUS (WINAPI *pRtlCreateMemoryZone)(PRTL_MEMORY_ZONE, SIZE_T, ULONG);
typedef PVOID (WINAPI *pRtlAllocateMemoryZone)(PRTL_MEMORY_ZONE, SIZE_T);

int main() {
    printf("=== RtlAllocateMemoryZone ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlCreateMemoryZone RtlCreateMemoryZone = 
        (pRtlCreateMemoryZone)GetProcAddress(ntdll, "RtlCreateMemoryZone");
    pRtlAllocateMemoryZone RtlAllocateMemoryZone = 
        (pRtlAllocateMemoryZone)GetProcAddress(ntdll, "RtlAllocateMemoryZone");
    
    RTL_MEMORY_ZONE zone = {0};
    RtlCreateMemoryZone(&zone, 4096, 0);
    
    PVOID result = RtlAllocateMemoryZone(&zone, 128);
    
    printf("Return Address: 0x%p\n", result);
    printf("Zone Address: 0x%p\n", &zone);
    printf("Size: %lu\n", 128);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}