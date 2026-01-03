#include <windows.h>
#include <stdio.h>

typedef BOOL (WINAPI *pCreateProcessInternalW)(
    HANDLE hToken,
    LPCWSTR lpApplicationName,
    LPWSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCWSTR lpCurrentDirectory,
    LPSTARTUPINFOW lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation,
    PHANDLE hNewToken
);

int main() {
    printf("=== CreateProcessInternalW ===\n");
    
    HMODULE kernel32 = LoadLibraryA("kernel32.dll");
    pCreateProcessInternalW CreateProcessInternalW = 
        (pCreateProcessInternalW)GetProcAddress(kernel32, "CreateProcessInternalW");
    
    STARTUPINFOW si = {0};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = {0};
    HANDLE newToken = NULL;
    
    BOOL result = CreateProcessInternalW(NULL, L"C:\\Windows\\System32\\notepad.exe", NULL, 
                                         NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi, &newToken);
    
    printf("Return Value: %d\n", result);
    printf("Token Handle: 0x%p\n", (HANDLE)NULL);
    printf("Application Name: C:\\Windows\\System32\\notepad.exe\n");
    printf("Process Handle: 0x%p\n", pi.hProcess);
    printf("Thread Handle: 0x%p\n", pi.hThread);
    printf("Process ID: %lu\n", pi.dwProcessId);
    printf("Thread ID: %lu\n", pi.dwThreadId);
    printf("New Token: 0x%p\n", newToken);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}