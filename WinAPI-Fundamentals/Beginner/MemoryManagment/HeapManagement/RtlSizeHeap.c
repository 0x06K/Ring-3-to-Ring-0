#include <windows.h>
#include <stdio.h>

typedef PVOID (NTAPI *pRtlAllocateHeap)(PVOID, ULONG, SIZE_T);
typedef SIZE_T (NTAPI *pRtlSizeHeap)(
    PVOID HeapHandle,
    ULONG Flags,
    PVOID BaseAddress
);

int main() {
    printf("=== RtlSizeHeap ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlAllocateHeap RtlAllocateHeap = (pRtlAllocateHeap)GetProcAddress(ntdll, "RtlAllocateHeap");
    pRtlSizeHeap RtlSizeHeap = (pRtlSizeHeap)GetProcAddress(ntdll, "RtlSizeHeap");
    
    HANDLE hHeap = GetProcessHeap();
    PVOID ptr = RtlAllocateHeap(hHeap, 0, 1024);
    SIZE_T size = RtlSizeHeap(hHeap, 0, ptr);
    
    printf("Allocation Size: %llu\n", (unsigned long long)size);
    printf("Address: 0x%p\n", ptr);
    printf("Heap Handle: 0x%p\n", hHeap);
    
    return 0;
}