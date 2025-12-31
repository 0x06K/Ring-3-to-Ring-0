#include <windows.h>
#include <winternl.h>
#include <stdio.h>

typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID;

typedef struct _THREAD_BASIC_INFORMATION64 {
    NTSTATUS ExitStatus;
    ULONGLONG TebBaseAddress;
    CLIENT_ID ClientId;
    ULONGLONG AffinityMask;
    LONG Priority;
    LONG BasePriority;
} THREAD_BASIC_INFORMATION64;

typedef NTSTATUS(NTAPI* NtWow64QueryInformationThread_t)(
    HANDLE ThreadHandle,
    THREADINFOCLASS ThreadInformationClass,
    PVOID ThreadInformation,
    ULONG ThreadInformationLength,
    PULONG ReturnLength
);

int main(void)
{
    NtWow64QueryInformationThread_t NtWow64QueryInformationThread =
        (NtWow64QueryInformationThread_t)GetProcAddress(
            GetModuleHandleA("ntdll.dll"),
            "NtWow64QueryInformationThread"
        );

    if (!NtWow64QueryInformationThread) {
        printf("NtWow64QueryInformationThread not found\n");
        return 1;
    }

    THREAD_BASIC_INFORMATION64 tbi64;
    NTSTATUS status = NtWow64QueryInformationThread(
        GetCurrentThread(),
        ThreadBasicInformation,
        &tbi64,
        sizeof(tbi64),
        NULL
    );

    if (status == 0) {
        printf("ExitStatus    : 0x%X\n", tbi64.ExitStatus);
        printf("TebBaseAddress: 0x%llX\n", tbi64.TebBaseAddress);
        printf("ClientId PID  : %p\n", tbi64.ClientId.UniqueProcess);
        printf("ClientId TID  : %p\n", tbi64.ClientId.UniqueThread);
        printf("AffinityMask  : 0x%llX\n", tbi64.AffinityMask);
        printf("Priority      : %ld\n", tbi64.Priority);
        printf("BasePriority  : %ld\n", tbi64.BasePriority);
    } else {
        printf("NtWow64QueryInformationThread failed: 0x%X\n", status);
    }

    return 0;
}
