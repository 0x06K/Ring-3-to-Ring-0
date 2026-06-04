#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtTestAlert)(void);

int main() {
    printf("=== NtTestAlert ===\n");

    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtTestAlert NtTestAlert =
        (pNtTestAlert)GetProcAddress(ntdll, "NtTestAlert");

    NTSTATUS status = NtTestAlert();

    printf("NTSTATUS: 0x%lx\n", status);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
