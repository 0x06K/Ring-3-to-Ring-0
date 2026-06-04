#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;

typedef struct _PS_CREATE_INFO {
    SIZE_T Size;
    ULONG State;
    union {
        struct {
            ULONG InitFlags;
            ACCESS_MASK AdditionalFileAccess;
        } InitState;
        struct {
            HANDLE FileHandle;
        } FailSection;
        struct {
            USHORT DllCharacteristics;
        } ExeFormat;
        struct {
            HANDLE IFEOKey;
        } ExeName;
        struct {
            NTSTATUS CreationStatus;
        } SuccessState;
    };
} PS_CREATE_INFO, *PPS_CREATE_INFO;

typedef NTSTATUS (WINAPI *pNtCreateUserProcess)(
    PHANDLE ProcessHandle,
    PHANDLE ThreadHandle,
    ACCESS_MASK ProcessDesiredAccess,
    ACCESS_MASK ThreadDesiredAccess,
    PVOID ProcessObjectAttributes,
    PVOID ThreadObjectAttributes,
    ULONG ProcessFlags,
    ULONG ThreadFlags,
    PVOID ProcessParameters,
    PPS_CREATE_INFO CreateInfo,
    PVOID AttributeList
);

int main() {
    printf("=== NtCreateUserProcess ===\n");
    
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtCreateUserProcess NtCreateUserProcess = 
        (pNtCreateUserProcess)GetProcAddress(ntdll, "NtCreateUserProcess");
    
    HANDLE processHandle;
    HANDLE threadHandle;
    PS_CREATE_INFO createInfo = {0};
    createInfo.Size = sizeof(createInfo);
    
    NTSTATUS status = NtCreateUserProcess(&processHandle, &threadHandle, 
                                          PROCESS_ALL_ACCESS, THREAD_ALL_ACCESS,
                                          NULL, NULL, 0, 0, NULL, &createInfo, NULL);
    
    printf("NTSTATUS: 0x%08lx\n", status);
    printf("Process Handle: 0x%p\n", processHandle);
    printf("Thread Handle: 0x%p\n", threadHandle);
    printf("Process Access: PROCESS_ALL_ACCESS\n");
    printf("Thread Access: THREAD_ALL_ACCESS\n");
    printf("Create Info Size: %zu\n", createInfo.Size);
    printf("Error Code: %lu\n", GetLastError());
    
    return 0;
}