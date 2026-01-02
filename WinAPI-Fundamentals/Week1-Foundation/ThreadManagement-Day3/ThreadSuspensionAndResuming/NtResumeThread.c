#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef NTSTATUS (WINAPI *pNtResumeThread)(
    HANDLE ThreadHandle,
    PULONG PreviousSuspendCount
);

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    Sleep(10000);
    return 0;
}

int main() {
    printf("=== NtResumeThread ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtResumeThread NtResumeThread = (pNtResumeThread)GetProcAddress(ntdll, "NtResumeThread");
    
    DWORD threadId;
    HANDLE thread = CreateThread(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, &threadId);
    ULONG previousCount;
    
    NTSTATUS status = NtResumeThread(thread, &previousCount);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Thread Handle: 0x%p\n", thread);
    printf("Thread ID: %lu\n", threadId);
    printf("Previous Suspend Count: %lu\n", previousCount);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}