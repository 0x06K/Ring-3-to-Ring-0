#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *NtWow64ReadVirtualMemory64_t)(
    HANDLE,
    ULONG64,
    PVOID,
    ULONG64,
    PULONG64
);

int main() {
    NtWow64ReadVirtualMemory64_t NtWow64ReadVirtualMemory64 =
        (NtWow64ReadVirtualMemory64_t)GetProcAddress(
            GetModuleHandleA("ntdll.dll"),
            "NtWow64ReadVirtualMemory64"
        );

    if (!NtWow64ReadVirtualMemory64) {
        printf("Function not found\n");
        return 1;
    }

    HANDLE hProc = GetCurrentProcess();

    ULONG64 address = 0x0000000140000000;  // example address
    BYTE buffer[32];
    ULONG64 bytesRead = 0;

    NTSTATUS status = NtWow64ReadVirtualMemory64(
        hProc,
        address,
        buffer,
        sizeof(buffer),
        &bytesRead
    );

    if (status == 0)
        printf("Read %llu bytes\n", bytesRead);
    else
        printf("Failed: NTSTATUS 0x%X\n", status);

    return 0;
}
