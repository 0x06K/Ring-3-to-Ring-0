#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef NTSTATUS (WINAPI *pRtlCreateUserThread)(
    HANDLE ProcessHandle,
    PSECURITY_DESCRIPTOR SecurityDescriptor,
    BOOLEAN CreateSuspended,
    ULONG StackZeroBits,
    SIZE_T StackReserve,
    SIZE_T StackCommit,
    PVOID StartAddress,
    PVOID Parameter,
    PHANDLE ThreadHandle,
    PCLIENT_ID ClientId
);

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    return 0;
}

int main() {
    printf("=== RtlCreateUserThread ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlCreateUserThread RtlCreateUserThread = 
        (pRtlCreateUserThread)GetProcAddress(ntdll, "RtlCreateUserThread");
    
    HANDLE threadHandle;
    CLIENT_ID clientId;
    
    NTSTATUS status = RtlCreateUserThread(GetCurrentProcess(), NULL, FALSE, 0, 0, 0, 
                                          (PVOID)ThreadProc, NULL, &threadHandle, &clientId);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Thread Handle: 0x%p\n", threadHandle);
    printf("Create Suspended: %d\n", FALSE);
    printf("Start Address: 0x%p\n", ThreadProc);
    printf("Parameter: 0x%p\n", (PVOID)NULL);
    printf("Client ID Process: 0x%p\n", clientId.UniqueProcess);
    printf("Client ID Thread: 0x%p\n", clientId.UniqueThread);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}