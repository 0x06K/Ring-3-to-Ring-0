#include <windows.h>
#include <winternl.h>
#include <stdio.h>

typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID;

typedef struct _THREAD_BASIC_INFORMATION {
    NTSTATUS ExitStatus;
    PVOID TebBaseAddress;
    CLIENT_ID ClientId;
    ULONG_PTR AffinityMask;
    LONG Priority;
    LONG BasePriority;
} THREAD_BASIC_INFORMATION;

typedef NTSTATUS(NTAPI* NtQueryInformationThread_t)(
    HANDLE ThreadHandle,
    THREADINFOCLASS ThreadInformationClass,
    PVOID ThreadInformation,
    ULONG ThreadInformationLength,
    PULONG ReturnLength
);

int main(void)
{
    NtQueryInformationThread_t NtQueryInformationThread =
        (NtQueryInformationThread_t)GetProcAddress(
            GetModuleHandleA("ntdll.dll"),
            "NtQueryInformationThread"
        );

    if (!NtQueryInformationThread) {
        printf("NtQueryInformationThread not found\n");
        return 1;
    }

    THREAD_BASIC_INFORMATION tbi;
    NTSTATUS status = NtQueryInformationThread(
        GetCurrentThread(),
        ThreadBasicInformation,
        &tbi,
        sizeof(tbi),
        NULL
    );

    if (status == 0) {
        printf("ExitStatus    : 0x%X\n", tbi.ExitStatus);
        printf("TebBaseAddress: %p\n", tbi.TebBaseAddress);
        printf("ClientId PID  : %p\n", tbi.ClientId.UniqueProcess);
        printf("ClientId TID  : %p\n", tbi.ClientId.UniqueThread);
        printf("AffinityMask  : 0x%p\n", tbi.AffinityMask);
        printf("Priority      : %ld\n", tbi.Priority);
        printf("BasePriority  : %ld\n", tbi.BasePriority);
    } else {
        printf("NtQueryInformationThread failed: 0x%X\n", status);
    }

    return 0;
}
