#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _INITIAL_TEB {
    PVOID StackBase;
    PVOID StackLimit;
    PVOID StackAllocationBase;
} INITIAL_TEB, *PINITIAL_TEB;

typedef NTSTATUS (WINAPI *pNtCreateThread)(
    PHANDLE ThreadHandle,
    ACCESS_MASK DesiredAccess,
    PVOID ObjectAttributes,
    HANDLE ProcessHandle,
    PCLIENT_ID ClientId,
    PVOID ThreadContext,
    PINITIAL_TEB InitialTeb,
    BOOLEAN CreateSuspended
);

int main() {
    printf("=== NtCreateThread ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtCreateThread NtCreateThread = (pNtCreateThread)GetProcAddress(ntdll, "NtCreateThread");
    
    HANDLE threadHandle;
    CLIENT_ID clientId = {0};
    INITIAL_TEB initialTeb = {0};
    
    NTSTATUS status = NtCreateThread(&threadHandle, THREAD_ALL_ACCESS, NULL, 
                                     GetCurrentProcess(), &clientId, NULL, &initialTeb, FALSE);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Thread Handle: 0x%p\n", threadHandle);
    printf("Desired Access: THREAD_ALL_ACCESS (0x%08lx)\n", THREAD_ALL_ACCESS);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Client ID Process: 0x%p\n", clientId.UniqueProcess);
    printf("Client ID Thread: 0x%p\n", clientId.UniqueThread);
    printf("Create Suspended: %d\n", FALSE);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}