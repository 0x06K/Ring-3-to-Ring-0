#include <windows.h>
#include <stdio.h>

typedef PVOID (NTAPI *pRtlCreateHeap)(
    ULONG Flags,
    PVOID HeapBase,
    SIZE_T ReserveSize,
    SIZE_T CommitSize,
    PVOID Lock,
    PVOID Parameters
);

int main() {
    printf("=== RtlCreateHeap ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlCreateHeap RtlCreateHeap = (pRtlCreateHeap)GetProcAddress(ntdll, "RtlCreateHeap");
    
    PVOID hHeap = RtlCreateHeap(0, NULL, 0, 4096, NULL, NULL);
    
    printf("Heap Handle: 0x%p\n", hHeap);
    
    return 0;
}