#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef NTSTATUS (WINAPI *pNtCreateSection)(PHANDLE, ACCESS_MASK, PVOID, PLARGE_INTEGER, ULONG, ULONG, HANDLE);
typedef NTSTATUS (WINAPI *pNtMapViewOfSectionEx)(
    HANDLE SectionHandle,
    HANDLE ProcessHandle,
    PVOID *BaseAddress,
    PLARGE_INTEGER SectionOffset,
    PSIZE_T ViewSize,
    ULONG AllocationType,
    ULONG PageProtection,
    PVOID ExtendedParameters,
    ULONG ExtendedParameterCount
);

int main() {
    printf("=== NtMapViewOfSectionEx ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtCreateSection NtCreateSection = (pNtCreateSection)GetProcAddress(ntdll, "NtCreateSection");
    pNtMapViewOfSectionEx NtMapViewOfSectionEx = 
        (pNtMapViewOfSectionEx)GetProcAddress(ntdll, "NtMapViewOfSectionEx");
    
    HANDLE section;
    LARGE_INTEGER sectionSize;
    sectionSize.QuadPart = 4096;
    NtCreateSection(&section, SECTION_ALL_ACCESS, NULL, &sectionSize, PAGE_READWRITE, SEC_COMMIT, NULL);
    
    PVOID baseAddress = NULL;
    SIZE_T viewSize = 0;
    
    NTSTATUS status = NtMapViewOfSectionEx(section, GetCurrentProcess(), &baseAddress, NULL, 
                                           &viewSize, 0, PAGE_READWRITE, NULL, 0);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Section Handle: 0x%p\n", section);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Base Address: 0x%p\n", baseAddress);
    printf("View Size: %zu\n", viewSize);
    printf("Page Protection: PAGE_READWRITE\n");
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}