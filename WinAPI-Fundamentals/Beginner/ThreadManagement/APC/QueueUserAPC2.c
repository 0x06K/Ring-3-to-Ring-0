#include <windows.h>
#include <stdio.h>

typedef DWORD (WINAPI *pQueueUserAPC2)(
    PAPCFUNC,
    HANDLE,
    ULONG_PTR,
    ULONG
);

void CALLBACK ApcProc(ULONG_PTR p) {}

int main() {
    printf("=== QueueUserAPC2 ===\n");

    HMODULE k32 = LoadLibraryA("kernel32.dll");
    pQueueUserAPC2 QueueUserAPC2 =
        (pQueueUserAPC2)GetProcAddress(k32, "QueueUserAPC2");

    DWORD ret = QueueUserAPC2(ApcProc, GetCurrentThread(), 0, 0);

    printf("Return Value (DWORD): %lu\n", ret);
    printf("Thread Handle: 0x%p\n", GetCurrentThread());
    printf("Error Code: %lu\n", GetLastError());
    return 0;
}
