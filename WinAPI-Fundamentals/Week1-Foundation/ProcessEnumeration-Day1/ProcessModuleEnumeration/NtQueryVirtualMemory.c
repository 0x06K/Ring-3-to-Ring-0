#include <windows.h>
#include <winternl.h>
#include <stdio.h>

typedef enum _MEMORY_INFORMATION_CLASS {
    MemoryBasicInformation,
    MemoryWorkingSetInformation,
    MemoryMappedFilenameInformation,
    MemoryRegionInformation,
    MemoryWorkingSetExInformation,
    MemorySharedCommitInformation,
    MemoryImageInformation,
    MemoryRegionInformationEx,
    MemoryPrivilegedBasicInformation,
    MemoryEnclaveImageInformation
} MEMORY_INFORMATION_CLASS;

typedef NTSTATUS (NTAPI *NtQueryVirtualMemory_t)(
    HANDLE,
    PVOID,
    MEMORY_INFORMATION_CLASS,
    PVOID,
    SIZE_T,
    PSIZE_T
);

int main() {
    NtQueryVirtualMemory_t NtQueryVirtualMemory =
        (NtQueryVirtualMemory_t)GetProcAddress(
            GetModuleHandleA("ntdll.dll"),
            "NtQueryVirtualMemory"
        );

    MEMORY_BASIC_INFORMATION mbi;
    SIZE_T retLen;

    NtQueryVirtualMemory(
        GetCurrentProcess(),
        NULL,
        MemoryBasicInformation,
        &mbi,
        sizeof(mbi),
        &retLen
    );

    printf("BaseAddress: %p\n", mbi.BaseAddress);
    printf("RegionSize : 0x%llx\n", (unsigned long long)mbi.RegionSize);
    printf("State      : 0x%lx\n", mbi.State);
    printf("Protect    : 0x%lx\n", mbi.Protect);

    return 0;
}
