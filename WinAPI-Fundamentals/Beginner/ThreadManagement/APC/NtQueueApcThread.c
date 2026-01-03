#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtQueueApcThread)(
    HANDLE,
    PVOID,
    PVOID,
    PVOID,
    PVOID
);

int main() {
    printf("=== NtQueueApcThread ===\n");

    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtQueueApcThread NtQueueApcThread =
        (pNtQueueApcThread)GetProcAddress(ntdll, "NtQueueApcThread");

    NTSTATUS status = NtQueueApcThread(
        GetCurrentThread(),
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
