#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _RTL_USER_PROCESS_INFORMATION {
    ULONG Length;
    HANDLE Process;
    HANDLE Thread;
    ULONG ProcessId;
    ULONG ThreadId;
} RTL_USER_PROCESS_INFORMATION, *PRTL_USER_PROCESS_INFORMATION;

typedef NTSTATUS (WINAPI *pRtlCreateUserProcess)(
    PUNICODE_STRING NtImagePathName,
    ULONG Attributes,
    PVOID ProcessParameters,
    PSECURITY_DESCRIPTOR ProcessSecurityDescriptor,
    PSECURITY_DESCRIPTOR ThreadSecurityDescriptor,
    HANDLE ParentProcess,
    BOOLEAN InheritHandles,
    HANDLE DebugPort,
    HANDLE ExceptionPort,
    PRTL_USER_PROCESS_INFORMATION ProcessInformation
);

int main() {
    printf("=== RtlCreateUserProcess ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pRtlCreateUserProcess RtlCreateUserProcess = 
        (pRtlCreateUserProcess)GetProcAddress(ntdll, "RtlCreateUserProcess");
    
    WCHAR imagePath[] = L"C:\\Windows\\System32\\notepad.exe";
    UNICODE_STRING imagePathStr;
    imagePathStr.Length = wcslen(imagePath) * sizeof(WCHAR);
    imagePathStr.MaximumLength = sizeof(imagePath);
    imagePathStr.Buffer = imagePath;
    
    RTL_USER_PROCESS_INFORMATION processInfo = {0};
    processInfo.Length = sizeof(processInfo);
    
    NTSTATUS status = RtlCreateUserProcess(&imagePathStr, 0, NULL, NULL, NULL, 
                                           NULL, FALSE, NULL, NULL, &processInfo);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Image Path: C:\\Windows\\System32\\notepad.exe\n");
    printf("Process Handle: 0x%p\n", processInfo.Process);
    printf("Thread Handle: 0x%p\n", processInfo.Thread);
    printf("Process ID: %lu\n", processInfo.ProcessId);
    printf("Thread ID: %lu\n", processInfo.ThreadId);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}