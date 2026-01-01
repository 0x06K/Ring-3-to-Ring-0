#include <windows.h>
#include <winternl.h>
#include <stdio.h>
#include <stdlib.h>

typedef NTSTATUS(NTAPI* NtQuerySystemInformation_t)(
    SYSTEM_INFORMATION_CLASS SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
);

// Complete SYSTEM_THREAD_INFORMATION structure
typedef struct _SYSTEM_THREAD_INFORMATION_FULL {
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER CreateTime;
    ULONG WaitTime;
    PVOID StartAddress;
    CLIENT_ID ClientId;
    LONG Priority;
    LONG BasePriority;
    ULONG ContextSwitches;
    ULONG ThreadState;
    ULONG WaitReason;
} SYSTEM_THREAD_INFORMATION_FULL, *PSYSTEM_THREAD_INFORMATION_FULL;

const char* ThreadStateToString(ULONG state) {
    switch (state) {
        case 0: return "Initialized";
        case 1: return "Ready";
        case 2: return "Running";
        case 3: return "Standby";
        case 4: return "Terminated";
        case 5: return "Waiting";
        case 6: return "Transition";
        case 7: return "DeferredReady";
        default: return "Unknown";
    }
}

const char* WaitReasonToString(ULONG reason) {
    switch (reason) {
        case 0: return "Executive";
        case 1: return "FreePage";
        case 2: return "PageIn";
        case 3: return "PoolAllocation";
        case 4: return "DelayExecution";
        case 5: return "Suspended";
        case 6: return "UserRequest";
        case 7: return "WrExecutive";
        case 8: return "WrFreePage";
        case 9: return "WrPageIn";
        case 10: return "WrPoolAllocation";
        case 11: return "WrDelayExecution";
        case 12: return "WrSuspended";
        case 13: return "WrUserRequest";
        case 14: return "WrEventPair";
        case 15: return "WrQueue";
        case 16: return "WrLpcReceive";
        case 17: return "WrLpcReply";
        case 18: return "WrVirtualMemory";
        case 19: return "WrPageOut";
        case 20: return "WrRendezvous";
        case 21: return "Spare2";
        case 22: return "Spare3";
        case 23: return "Spare4";
        case 24: return "Spare5";
        case 25: return "WrCalloutStack";
        case 26: return "WrKernel";
        case 27: return "WrResource";
        case 28: return "WrPushLock";
        case 29: return "WrMutex";
        case 30: return "WrQuantumEnd";
        case 31: return "WrDispatchInt";
        case 32: return "WrPreempted";
        case 33: return "WrYieldExecution";
        case 34: return "WrFastMutex";
        case 35: return "WrGuardedMutex";
        case 36: return "WrRundown";
        default: return "Unknown";
    }
}

int main(void) {
    NtQuerySystemInformation_t NtQuerySystemInformation = 
        (NtQuerySystemInformation_t)GetProcAddress(
            GetModuleHandleA("ntdll.dll"), 
            "NtQuerySystemInformation"
        );
    
    if (!NtQuerySystemInformation) {
        printf("NtQuerySystemInformation not found\n");
        return 1;
    }

    ULONG size = 1024 * 1024 * 2; // Increase buffer size
    PVOID buffer = malloc(size);
    if (!buffer) {
        printf("Memory allocation failed\n");
        return 1;
    }

    ULONG returnLength = 0;
    NTSTATUS status = NtQuerySystemInformation(
        SystemProcessInformation,
        buffer,
        size,
        &returnLength
    );

    if (status != 0) {
        printf("NtQuerySystemInformation failed: 0x%X\n", status);
        free(buffer);
        return 1;
    }

    PSYSTEM_PROCESS_INFORMATION spi = (PSYSTEM_PROCESS_INFORMATION)buffer;

    // Iterate all processes
    while (1) {
        // Print process information
        if (spi->ImageName.Buffer) {
            wprintf(L"\n========================================\n");
            wprintf(L"Process: %s\n", spi->ImageName.Buffer);
            wprintf(L"========================================\n");
        } else {
            printf("\n========================================\n");
            printf("Process: System Idle Process\n");
            printf("========================================\n");
        }
        printf("Process ID: %llu\n", (unsigned long long)(ULONG_PTR)spi->UniqueProcessId);
        printf("Thread Count: %u\n\n", spi->NumberOfThreads);

        PSYSTEM_THREAD_INFORMATION_FULL threads = 
            (PSYSTEM_THREAD_INFORMATION_FULL)((BYTE*)spi + sizeof(SYSTEM_PROCESS_INFORMATION));

        for (ULONG i = 0; i < spi->NumberOfThreads; i++) {
            PSYSTEM_THREAD_INFORMATION_FULL t = &threads[i];
            
            printf("  Thread #%u:\n", i + 1);
            printf("  ----------------------------------------\n");
            
            // Thread identification
            printf("  Thread ID (TID):        %llu\n", (unsigned long long)(ULONG_PTR)t->ClientId.UniqueThread);
            printf("  Process ID (PID):       %llu\n", (unsigned long long)(ULONG_PTR)t->ClientId.UniqueProcess);
            
            // Kernel times
            printf("  Kernel Time:            %llu (100ns units)\n", t->KernelTime.QuadPart);
            printf("  User Time:              %llu (100ns units)\n", t->UserTime.QuadPart);
            
            // Start address and time
            printf("  Start Address:          0x%p\n", t->StartAddress);
            printf("  Create Time:            %llu\n", t->CreateTime.QuadPart);
            
            // Wait information
            printf("  Wait Time:              %u\n", t->WaitTime);
            
            // Thread state and priority
            printf("  Thread State:           %u (%s)\n", t->ThreadState, ThreadStateToString(t->ThreadState));
            printf("  Wait Reason:            %u (%s)\n", t->WaitReason, WaitReasonToString(t->WaitReason));
            printf("  Priority:               %d\n", t->Priority);
            printf("  Base Priority:          %d\n", t->BasePriority);
            
            // Context switches
            printf("  Context Switches:       %u\n", t->ContextSwitches);
            
            printf("\n");
        }

        if (spi->NextEntryOffset == 0)
            break;
        
        spi = (PSYSTEM_PROCESS_INFORMATION)((BYTE*)spi + spi->NextEntryOffset);
    }

    free(buffer);
    return 0;
}
