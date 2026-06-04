#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *NtWow64QueryInformationProcess64_t)(
    HANDLE,
    ULONG,
    PVOID,
    ULONG,
    PULONG
);

typedef struct _PROCESS_BASIC_INFORMATION64 {
    ULONGLONG Reserved1;
    ULONGLONG PebBaseAddress;
    ULONGLONG Reserved2[2];
    ULONGLONG UniqueProcessId;
    ULONGLONG Reserved3;
} PROCESS_BASIC_INFORMATION64;

int main() {
    NtWow64QueryInformationProcess64_t NtWow64QueryInformationProcess64 =
        (NtWow64QueryInformationProcess64_t)GetProcAddress(
            GetModuleHandleA("ntdll.dll"),
            "NtWow64QueryInformationProcess64"
        );

    PROCESS_BASIC_INFORMATION64 pbi;
    ULONG retLen = 0;

    NTSTATUS status = NtWow64QueryInformationProcess64(
        GetCurrentProcess(),
        0, // ProcessBasicInformation
        &pbi,
        sizeof(pbi),
        &retLen
    );

    if (status == 0) {
        printf("64-bit PEB: 0x%llx\n", pbi.PebBaseAddress);
        printf("PID: %llu\n", pbi.UniqueProcessId);
    } else {
        printf("Failed: NTSTATUS 0x%X\n", status);
    }

    return 0;
}
