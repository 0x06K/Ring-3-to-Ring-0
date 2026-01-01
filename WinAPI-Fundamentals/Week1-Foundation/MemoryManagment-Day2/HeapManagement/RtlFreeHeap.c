#include <windows.h>
#include <stdio.h>

typedef PVOID (NTAPI *pRtlAllocateHeap)(PVOID, ULONG, SIZE_T);
typedef BOOLEAN (NTAPI *pRtlFreeHeap)(
    PVOID HeapHandle,
    ULONG Flags,
    PVOID BaseAddress
);

int main() {
    printf("=== RtlFreeHeap ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlAllocateHeap RtlAllocateHeap = (pRtlAllocateHeap)GetProcAddress(ntdll, "RtlAllocateHeap");
    pRtlFreeHeap RtlFreeHeap = (pRtlFreeHeap)GetProcAddress(ntdll, "RtlFreeHeap");
    
    HANDLE hHeap = GetProcessHeap();
    PVOID ptr = RtlAllocateHeap(hHeap, 0, 1024);
    BOOLEAN result = RtlFreeHeap(hHeap, 0, ptr);
    
    printf("Return Value: %d\n", result);
    printf("Freed Address: 0x%p\n", ptr);
    printf("Heap Handle: 0x%p\n", hHeap);
    
    return 0;
}