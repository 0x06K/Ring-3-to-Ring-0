#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtQueueApcThreadEx)(
    HANDLE,
    HANDLE,
    PVOID,
    PVOID,
    PVOID,
    PVOID
);

int main() {
    printf("=== NtQueueApcThreadEx ===\n");

    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtQueueApcThreadEx NtQueueApcThreadEx =
        (pNtQueueApcThreadEx)GetProcAddress(ntdll, "NtQueueApcThreadEx");

    NTSTATUS status = NtQueueApcThreadEx(
        GetCurrentThread(),
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    );

    printf("NTSTATUS: 0x%lx\n", status);
    printf("Thread Handle: 0x%p\n", GetCurrentThread());
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
