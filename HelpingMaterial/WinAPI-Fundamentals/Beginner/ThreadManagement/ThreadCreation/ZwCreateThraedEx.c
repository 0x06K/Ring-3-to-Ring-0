#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef NTSTATUS (WINAPI *pZwCreateThreadEx)(
    PHANDLE ThreadHandle,
    ACCESS_MASK DesiredAccess,
    PVOID ObjectAttributes,
    HANDLE ProcessHandle,
    PVOID StartRoutine,
    PVOID Argument,
    ULONG CreateFlags,
    SIZE_T ZeroBits,
    SIZE_T StackSize,
    SIZE_T MaximumStackSize,
    PVOID AttributeList
);

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    return 0;
}

int main() {
    printf("=== ZwCreateThreadEx ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pZwCreateThreadEx ZwCreateThreadEx = (pZwCreateThreadEx)GetProcAddress(ntdll, "ZwCreateThreadEx");
    
    HANDLE threadHandle;
    
    NTSTATUS status = ZwCreateThreadEx(&threadHandle, THREAD_ALL_ACCESS, NULL, 
                                       GetCurrentProcess(), (PVOID)ThreadProc, NULL, 
                                       0, 0, 0, 0, NULL);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Thread Handle: 0x%p\n", threadHandle);
    printf("Desired Access: THREAD_ALL_ACCESS (0x%08lx)\n", THREAD_ALL_ACCESS);
    printf("Process Handle: 0x%p\n", GetCurrentProcess());
    printf("Start Routine: 0x%p\n", ThreadProc);
    printf("Argument: 0x%p\n", (PVOID)NULL);
    printf("Create Flags: %lu\n", 0);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}