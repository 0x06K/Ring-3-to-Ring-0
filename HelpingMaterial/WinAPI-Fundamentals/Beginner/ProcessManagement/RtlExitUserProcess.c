#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef VOID (WINAPI *pRtlExitUserProcess)(NTSTATUS ExitStatus);

int main() {
    printf("=== RtlExitUserProcess ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlExitUserProcess RtlExitUserProcess = 
        (pRtlExitUserProcess)GetProcAddress(ntdll, "RtlExitUserProcess");
    
    NTSTATUS exitStatus = 123;
    
    printf("Exit Status: 0x%08lx\n", exitStatus);
    printf("About to exit...\n");
    
    RtlExitUserProcess(exitStatus);
    
    printf("This line should never be reached\n");
    
    return 0;
}