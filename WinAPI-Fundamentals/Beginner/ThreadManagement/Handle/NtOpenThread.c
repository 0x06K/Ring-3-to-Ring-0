#include <windows.h>
#include <stdio.h>

typedef NTSTATUS (NTAPI *pNtOpenThread)(
    PHANDLE,
    ACCESS_MASK,
    POBJECT_ATTRIBUTES,
    PCLIENT_ID
);

int main() {
    printf("=== NtOpenThread ===\n");

    HANDLE hThread = NULL;
    CLIENT_ID cid = {0};
    OBJECT_ATTRIBUTES oa = {0};

    cid.UniqueThread = (HANDLE)(ULONG_PTR)GetCurrentThreadId();

    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtOpenThread NtOpenThread =
        (pNtOpenThread)GetProcAddress(ntdll, "NtOpenThread");

    NTSTATUS status = NtOpenThread(
        &hThread,
        THREAD_ALL_ACCESS,
        &oa,
        &cid
    );

    printf("NTSTATUS: 0x%lx\n", status);
    printf("Thread Handle: 0x%p\n", hThread);
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
