#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtSetInformationThread)(
    HANDLE,
    ULONG,
    PVOID,
    ULONG
);

int main() {
    printf("=== NtSetInformationThread ===\n");

    ULONG info = 0;

    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtSetInformationThread NtSetInformationThread =
        (pNtSetInformationThread)GetProcAddress(ntdll, "NtSetInformationThread");

    NTSTATUS status = NtSetInformationThread(
        GetCurrentThread(),
        0,
        &info,
        sizeof(info)
    );

    printf("NTSTATUS: 0x%lx\n", status);
    printf("Info Address: 0x%p\n", &info);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
