#include <windows.h>
#include <stdio.h>

typedef VOID (NTAPI *pRtlExitUserThread)(
    NTSTATUS ExitStatus
);

int main() {
    printf("=== RtlExitUserThread ===\n");

    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlExitUserThread RtlExitUserThread =
        (pRtlExitUserThread)GetProcAddress(ntdll, "RtlExitUserThread");

    RtlExitUserThread(0xCAFE);

    printf("Return Value: void (no return)\n");
    printf("Exit Status: 0xCAFE\n");
    printf("Error Code: %lu\n", GetLastError());

    return 0;
}
