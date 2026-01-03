#include <windows.h>
#include <stdio.h>

typedef struct _SECTION_BASIC_INFORMATION {
    PVOID BaseAddress;
    ULONG AllocationAttributes;
    LARGE_INTEGER MaximumSize;
} SECTION_BASIC_INFORMATION, *PSECTION_BASIC_INFORMATION;

typedef NTSTATUS (NTAPI *pNtCreateSection)(PHANDLE, ACCESS_MASK, PVOID, PLARGE_INTEGER, ULONG, ULONG, HANDLE);
typedef NTSTATUS (NTAPI *pNtQuerySection)(
    HANDLE SectionHandle,
    ULONG SectionInformationClass,
    PVOID SectionInformation,
    SIZE_T SectionInformationLength,
    PSIZE_T ReturnLength
);

int main() {
    printf("=== NtQuerySection ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtCreateSection NtCreateSection = (pNtCreateSection)GetProcAddress(ntdll, "NtCreateSection");
    pNtQuerySection NtQuerySection = (pNtQuerySection)GetProcAddress(ntdll, "NtQuerySection");
    
    HANDLE hSection = NULL;
    LARGE_INTEGER maxSize;
    maxSize.QuadPart = 4096;
    NtCreateSection(&hSection, SECTION_ALL_ACCESS, NULL, &maxSize, PAGE_READWRITE, SEC_COMMIT, NULL);
    
    SECTION_BASIC_INFORMATION info;
    SIZE_T returnLength;
    NTSTATUS status = NtQuerySection(hSection, 0, &info, sizeof(info), &returnLength);
    
    printf("NTSTATUS: 0x%08lX\n", (unsigned long)status);
    printf("Section Handle: 0x%p\n", hSection);
    printf("Base Address: 0x%p\n", info.BaseAddress);
    printf("Allocation Attributes: 0x%08lX\n", info.AllocationAttributes);
    printf("Maximum Size: %lld\n", (long long)info.MaximumSize.QuadPart);
    printf("Return Length: %llu\n", (unsigned long long)returnLength);
    
    return 0;
}