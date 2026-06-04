#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtCreateSection)(PHANDLE, ACCESS_MASK, PVOID, PLARGE_INTEGER, ULONG, ULONG, HANDLE);
typedef NTSTATUS (NTAPI *pNtMapViewOfSection)(
    HANDLE SectionHandle,
    HANDLE ProcessHandle,
    PVOID *BaseAddress,
    ULONG_PTR ZeroBits,
    SIZE_T CommitSize,
    PLARGE_INTEGER SectionOffset,
    PSIZE_T ViewSize,
    ULONG InheritDisposition,
    ULONG AllocationType,
    ULONG Win32Protect
);

int main() {
    printf("=== NtMapViewOfSection ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtCreateSection NtCreateSection = (pNtCreateSection)GetProcAddress(ntdll, "NtCreateSection");
    pNtMapViewOfSection NtMapViewOfSection = (pNtMapViewOfSection)GetProcAddress(ntdll, "NtMapViewOfSection");
    
    HANDLE hSection = NULL;
    LARGE_INTEGER maxSize;
    maxSize.QuadPart = 4096;
    NtCreateSection(&hSection, SECTION_ALL_ACCESS, NULL, &maxSize, PAGE_READWRITE, SEC_COMMIT, NULL);
    
    PVOID baseAddr = NULL;
    SIZE_T viewSize = 4096;
    NTSTATUS status = NtMapViewOfSection(hSection, GetCurrentProcess(), &baseAddr, 0, 0, NULL, &viewSize, 1, 0, PAGE_READWRITE);
    
    printf("NTSTATUS: 0x%08lX\n", (unsigned long)status);
    printf("Base Address: 0x%p\n", baseAddr);
    printf("View Size: %llu\n", (unsigned long long)viewSize);
    printf("Section Handle: 0x%p\n", hSection);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    
    return 0;
}