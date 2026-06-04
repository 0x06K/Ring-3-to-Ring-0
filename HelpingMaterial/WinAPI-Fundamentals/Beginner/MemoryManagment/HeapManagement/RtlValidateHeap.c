#include <windows.h>
#include <stdio.h>

typedef PVOID (NTAPI *pRtlAllocateHeap)(PVOID, ULONG, SIZE_T);
typedef BOOLEAN (NTAPI *pRtlValidateHeap)(
    PVOID HeapHandle,
    ULONG Flags,
    PVOID BaseAddress
);

int main() {
    printf("=== RtlValidateHeap ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlAllocateHeap RtlAllocateHeap = (pRtlAllocateHeap)GetProcAddress(ntdll, "RtlAllocateHeap");
    pRtlValidateHeap RtlValidateHeap = (pRtlValidateHeap)GetProcAddress(ntdll, "RtlValidateHeap");
    
    HANDLE hHeap = GetProcessHeap();
    PVOID ptr = RtlAllocateHeap(hHeap, 0, 1024);
    BOOLEAN result = RtlValidateHeap(hHeap, 0, ptr);
    
    printf("Return Value: %d\n", result);
    printf("Heap Handle: 0x%p\n", hHeap);
    printf("Address Validated: 0x%p\n", ptr);
    
    return 0;
}