#include <windows.h>
#include <stdio.h>

typedef BOOLEAN (NTAPI *pRtlLockHeap)(PVOID HeapHandle);

int main() {
    printf("=== RtlLockHeap ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlLockHeap RtlLockHeap = (pRtlLockHeap)GetProcAddress(ntdll, "RtlLockHeap");
    
    HANDLE hHeap = GetProcessHeap();
    BOOLEAN result = RtlLockHeap(hHeap);
    
    printf("Return Value: %d\n", result);
    printf("Heap Handle: 0x%p\n", hHeap);
    
    return 0;
}