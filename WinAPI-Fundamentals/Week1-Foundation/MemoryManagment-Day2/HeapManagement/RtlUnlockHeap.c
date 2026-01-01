#include <windows.h>
#include <stdio.h>

typedef BOOLEAN (NTAPI *pRtlLockHeap)(PVOID);
typedef BOOLEAN (NTAPI *pRtlUnlockHeap)(PVOID HeapHandle);

int main() {
    printf("=== RtlUnlockHeap ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlLockHeap RtlLockHeap = (pRtlLockHeap)GetProcAddress(ntdll, "RtlLockHeap");
    pRtlUnlockHeap RtlUnlockHeap = (pRtlUnlockHeap)GetProcAddress(ntdll, "RtlUnlockHeap");
    
    HANDLE hHeap = GetProcessHeap();
    RtlLockHeap(hHeap);
    BOOLEAN result = RtlUnlockHeap(hHeap);
    
    printf("Return Value: %d\n", result);
    printf("Heap Handle: 0x%p\n", hHeap);
    
    return 0;
}