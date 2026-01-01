#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtCreateSection)(
    PHANDLE SectionHandle,
    ACCESS_MASK DesiredAccess,
    PVOID ObjectAttributes,
    PLARGE_INTEGER MaximumSize,
    ULONG SectionPageProtection,
    ULONG AllocationAttributes,
    HANDLE FileHandle
);

int main() {
    printf("=== NtCreateSection ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtCreateSection NtCreateSection = (pNtCreateSection)GetProcAddress(ntdll, "NtCreateSection");
    
    HANDLE hSection = NULL;
    LARGE_INTEGER maxSize;
    maxSize.QuadPart = 4096;
    NTSTATUS status = NtCreateSection(&hSection, SECTION_ALL_ACCESS, NULL, &maxSize, PAGE_READWRITE, SEC_COMMIT, NULL);
    
    printf("NTSTATUS: 0x%08lX\n", (unsigned long)status);
    printf("Section Handle: 0x%p\n", hSection);
    printf("Maximum Size: %lld\n", (long long)maxSize.QuadPart);
    printf("Page Protection: PAGE_READWRITE\n");
    printf("Allocation Attributes: SEC_COMMIT\n");
    
    return 0;
}