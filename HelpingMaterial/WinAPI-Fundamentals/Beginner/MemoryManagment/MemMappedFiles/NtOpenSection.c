#include <windows.h>
#include <stdio.h>

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;
    PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef NTSTATUS (NTAPI *pNtOpenSection)(
    PHANDLE SectionHandle,
    ACCESS_MASK DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes
);

int main() {
    printf("=== NtOpenSection ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtOpenSection NtOpenSection = (pNtOpenSection)GetProcAddress(ntdll, "NtOpenSection");
    
    HANDLE hSection = NULL;
    NTSTATUS status = NtOpenSection(&hSection, SECTION_ALL_ACCESS, NULL);
    
    printf("NTSTATUS: 0x%08lX\n", (unsigned long)status);
    printf("Section Handle: 0x%p\n", hSection);
    printf("Desired Access: SECTION_ALL_ACCESS\n");
    
    return 0;
}