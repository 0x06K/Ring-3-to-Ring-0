#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtWaitForSingleObject)(
    HANDLE,
    BOOLEAN,
    PLARGE_INTEGER
);

int main() {
    printf("=== NtWaitForSingleObject ===\n");

    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtWaitForSingleObject NtWaitForSingleObject =
        (pNtWaitForSingleObject)GetProcAddress(ntdll, "NtWaitForSingleObject");

    NTSTATUS status = NtWaitForSingleObject(GetCurrentThread(), TRUE, NULL);

    printf("NTSTATUS: 0x%lx\n", status);
    printf("Handle: 0x%p\n", GetCurrentThread());
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
