#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtCreateSection)(PHANDLE, ACCESS_MASK, PVOID, PLARGE_INTEGER, ULONG, ULONG, HANDLE);
typedef NTSTATUS (NTAPI *pNtExtendSection)(
    HANDLE SectionHandle,
    PLARGE_INTEGER NewSectionSize
);

int main() {
    printf("=== NtExtendSection ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtCreateSection NtCreateSection = (pNtCreateSection)GetProcAddress(ntdll, "NtCreateSection");
    pNtExtendSection NtExtendSection = (pNtExtendSection)GetProcAddress(ntdll, "NtExtendSection");
    
    HANDLE hSection = NULL;
    LARGE_INTEGER maxSize;
    maxSize.QuadPart = 4096;
    NtCreateSection(&hSection, SECTION_ALL_ACCESS, NULL, &maxSize, PAGE_READWRITE, SEC_COMMIT, NULL);
    
    LARGE_INTEGER newSize;
    newSize.QuadPart = 8192;
    NTSTATUS status = NtExtendSection(hSection, &newSize);
    
    printf("NTSTATUS: 0x%08lX\n", (unsigned long)status);
    printf("Section Handle: 0x%p\n", hSection);
    printf("Original Size: 4096\n");
    printf("New Size: %lld\n", (long long)newSize.QuadPart);
    
    return 0;
}