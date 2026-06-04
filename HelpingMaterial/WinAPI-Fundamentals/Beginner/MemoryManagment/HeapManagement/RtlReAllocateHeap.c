#include <windows.h>
#include <stdio.h>

typedef PVOID (NTAPI *pRtlAllocateHeap)(PVOID, ULONG, SIZE_T);
typedef PVOID (NTAPI *pRtlReAllocateHeap)(
    PVOID HeapHandle,
    ULONG Flags,
    PVOID BaseAddress,
    SIZE_T Size
);

int main() {
    printf("=== RtlReAllocateHeap ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlAllocateHeap RtlAllocateHeap = (pRtlAllocateHeap)GetProcAddress(ntdll, "RtlAllocateHeap");
    pRtlReAllocateHeap RtlReAllocateHeap = (pRtlReAllocateHeap)GetProcAddress(ntdll, "RtlReAllocateHeap");
    
    HANDLE hHeap = GetProcessHeap();
    PVOID ptr = RtlAllocateHeap(hHeap, 0, 1024);
    PVOID newPtr = RtlReAllocateHeap(hHeap, 0, ptr, 2048);
    
    printf("Original Address: 0x%p\n", ptr);
    printf("New Address: 0x%p\n", newPtr);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("New Size: 2048\n");
    
    return 0;
}