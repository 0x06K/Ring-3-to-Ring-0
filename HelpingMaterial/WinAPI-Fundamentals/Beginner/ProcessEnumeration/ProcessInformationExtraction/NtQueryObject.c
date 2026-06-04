#include <windows.h>
#include <stdio.h>
#include <winternl.h>

#pragma comment(lib, "ntdll.lib")

// NTSTATUS helper
#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#endif


// Structure returned for ObjectNameInformation
typedef struct _OBJECT_NAME_INFORMATION {
    UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION;

typedef NTSTATUS (NTAPI *pNtQueryObject)(
    HANDLE,
    OBJECT_INFORMATION_CLASS,
    PVOID,
    ULONG,
    PULONG
);

int main()
{
    // Open a test file
    HANDLE hFile = CreateFileW(L"C:\\Windows\\System32\\notepad.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Failed to open file\n");
        return 1;
    }

    // Load NtQueryObject
    pNtQueryObject NtQueryObject =
        (pNtQueryObject)GetProcAddress(
            GetModuleHandleW(L"ntdll.dll"),
            "NtQueryObject"
        );

    if (!NtQueryObject) {
        printf("NtQueryObject not found\n");
        CloseHandle(hFile);
        return 1;
    }

    BYTE buffer[1024];
    ULONG returnLength = 0;

    NTSTATUS status = NtQueryObject(
        hFile,
        ObjectNameInformation,
        buffer,
        sizeof(buffer),
        &returnLength
    );

    if (NT_SUCCESS(status)) {
        POBJECT_NAME_INFORMATION nameInfo =
            (POBJECT_NAME_INFORMATION)buffer;

        wprintf(L"Object name: %wZ\n", &nameInfo->Name);
    } else {
        printf("NtQueryObject failed: 0x%X\n", status);
    }

    CloseHandle(hFile);
    return 0;
}
