#include <windows.h>
#include <stdio.h>

typedef PVOID (NTAPI *pRtlAllocateHeap)(
    PVOID HeapHandle,
    ULONG Flags,
    SIZE_T Size
);

int main() {
    printf("=== RtlAllocateHeap ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlAllocateHeap RtlAllocateHeap = (pRtlAllocateHeap)GetProcAddress(ntdll, "RtlAllocateHeap");
    
    HANDLE hHeap = GetProcessHeap();
    PVOID ptr = RtlAllocateHeap(hHeap, 0, 1024);
    
    printf("Allocated Address: 0x%p\n", ptr);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Size Requested: 1024\n");
    
    return 0;
}