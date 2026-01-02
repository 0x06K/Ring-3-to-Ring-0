#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtWaitForMultipleObjects)(
    ULONG,
    HANDLE*,
    BOOLEAN,
    BOOLEAN,
    PLARGE_INTEGER
);

int main() {
    printf("=== NtWaitForMultipleObjects ===\n");

    HANDLE h[1] = { GetCurrentThread() };

    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtWaitForMultipleObjects NtWaitForMultipleObjects =
        (pNtWaitForMultipleObjects)GetProcAddress(ntdll, "NtWaitForMultipleObjects");

    NTSTATUS status = NtWaitForMultipleObjects(1, h, FALSE, TRUE, NULL);

    printf("NTSTATUS: 0x%lx\n", status);
    printf("Handle[0]: 0x%p\n", h[0]);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
