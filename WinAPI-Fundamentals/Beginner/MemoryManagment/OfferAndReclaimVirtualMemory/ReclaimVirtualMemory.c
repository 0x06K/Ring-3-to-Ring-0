#include <windows.h>
#include <stdio.h>

typedef enum _OFFER_PRIORITY {
    VmOfferPriorityVeryLow = 1,
    VmOfferPriorityLow,
    VmOfferPriorityBelowNormal,
    VmOfferPriorityNormal
} OFFER_PRIORITY;

typedef DWORD (WINAPI *pOfferVirtualMemory)(PVOID, SIZE_T, OFFER_PRIORITY);
typedef DWORD (WINAPI *pReclaimVirtualMemory)(PVOID, SIZE_T);

int main() {
    printf("=== ReclaimVirtualMemory ===\n");
    
    HMODULE kernel32 = LoadLibraryA("kernel32.dll");
    pOfferVirtualMemory OfferVirtualMemory = (pOfferVirtualMemory)GetProcAddress(kernel32, "OfferVirtualMemory");
    pReclaimVirtualMemory ReclaimVirtualMemory = (pReclaimVirtualMemory)GetProcAddress(kernel32, "ReclaimVirtualMemory");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    OfferVirtualMemory(addr, 4096, VmOfferPriorityNormal);
    
    DWORD result = ReclaimVirtualMemory(addr, 4096);
    
    printf("Return Value: %lu\n", result);
    printf("Virtual Address: 0x%p\n", addr);
    printf("Size: %lu\n", 4096);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}