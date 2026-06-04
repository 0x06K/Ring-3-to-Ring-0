#include <windows.h>
#include <stdio.h>

typedef PVOID (NTAPI *pRtlCreateHeap)(ULONG, PVOID, SIZE_T, SIZE_T, PVOID, PVOID);
typedef PVOID (NTAPI *pRtlDestroyHeap)(PVOID HeapHandle);

int main() {
    printf("=== RtlDestroyHeap ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlCreateHeap RtlCreateHeap = (pRtlCreateHeap)GetProcAddress(ntdll, "RtlCreateHeap");
    pRtlDestroyHeap RtlDestroyHeap = (pRtlDestroyHeap)GetProcAddress(ntdll, "RtlDestroyHeap");
    
    PVOID hHeap = RtlCreateHeap(0, NULL, 0, 4096, NULL, NULL);
    PVOID result = RtlDestroyHeap(hHeap);
    
    printf("Return Value: 0x%p\n", result);
    printf("Heap Handle: 0x%p\n", hHeap);
    
    return 0;
}