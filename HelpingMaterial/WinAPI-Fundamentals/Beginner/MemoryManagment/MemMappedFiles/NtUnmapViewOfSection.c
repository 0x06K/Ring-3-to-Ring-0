#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtCreateSection)(PHANDLE, ACCESS_MASK, PVOID, PLARGE_INTEGER, ULONG, ULONG, HANDLE);
typedef NTSTATUS (NTAPI *pNtMapViewOfSection)(HANDLE, HANDLE, PVOID*, ULONG_PTR, SIZE_T, PLARGE_INTEGER, PSIZE_T, ULONG, ULONG, ULONG);
typedef NTSTATUS (NTAPI *pNtUnmapViewOfSection)(
    HANDLE ProcessHandle,
    PVOID BaseAddress
);

int main() {
    printf("=== NtUnmapViewOfSection ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtCreateSection NtCreateSection = (pNtCreateSection)GetProcAddress(ntdll, "NtCreateSection");
    pNtMapViewOfSection NtMapViewOfSection = (pNtMapViewOfSection)GetProcAddress(ntdll, "NtMapViewOfSection");
    pNtUnmapViewOfSection NtUnmapViewOfSection = (pNtUnmapViewOfSection)GetProcAddress(ntdll, "NtUnmapViewOfSection");
    
    HANDLE hSection = NULL;
    LARGE_INTEGER maxSize;
    maxSize.QuadPart = 4096;
    NtCreateSection(&hSection, SECTION_ALL_ACCESS, NULL, &maxSize, PAGE_READWRITE, SEC_COMMIT, NULL);
    
    PVOID baseAddr = NULL;
    SIZE_T viewSize = 4096;
    NtMapViewOfSection(hSection, GetCurrentProcess(), &baseAddr, 0, 0, NULL, &viewSize, 1, 0, PAGE_READWRITE);
    
    NTSTATUS status = NtUnmapViewOfSection(GetCurrentProcess(), baseAddr);
    
    printf("NTSTATUS: 0x%08lX\n", (unsigned long)status);
    printf("Base Address: 0x%p\n", baseAddr);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Section Handle: 0x%p\n", hSection);
    
    return 0;
}