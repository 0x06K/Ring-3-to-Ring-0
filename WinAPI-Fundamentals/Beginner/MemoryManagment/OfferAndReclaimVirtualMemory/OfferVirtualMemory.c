#include <windows.h>
#include <stdio.h>

typedef enum _OFFER_PRIORITY {
    VmOfferPriorityVeryLow = 1,
    VmOfferPriorityLow,
    VmOfferPriorityBelowNormal,
    VmOfferPriorityNormal
} OFFER_PRIORITY;

typedef DWORD (WINAPI *pOfferVirtualMemory)(
    PVOID VirtualAddress,
    SIZE_T Size,
    OFFER_PRIORITY Priority
);

int main() {
    printf("=== OfferVirtualMemory ===\n");
    
    HMODULE kernel32 = LoadLibraryA("kernel32.dll");
    pOfferVirtualMemory OfferVirtualMemory = (pOfferVirtualMemory)GetProcAddress(kernel32, "OfferVirtualMemory");
    
    LPVOID addr = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    DWORD result = OfferVirtualMemory(addr, 4096, VmOfferPriorityNormal);
    
    printf("Return Value: %lu\n", result);
    printf("Virtual Address: 0x%p\n", addr);
    printf("Size: %lu\n", 4096);
    printf("Priority: VmOfferPriorityNormal (%d)\n", VmOfferPriorityNormal);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}