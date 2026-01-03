#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtDelayExecution)(
    BOOLEAN Alertable,
    PLARGE_INTEGER DelayInterval
);

int main() {
    printf("=== NtDelayExecution ===\n");

    LARGE_INTEGER delay;
    delay.QuadPart = -10000000;

    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtDelayExecution NtDelayExecution =
        (pNtDelayExecution)GetProcAddress(ntdll, "NtDelayExecution");

    NTSTATUS status = NtDelayExecution(TRUE, &delay);

    printf("NTSTATUS: 0x%lx\n", status);
    printf("DelayInterval: %lld\n", delay.QuadPart);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
