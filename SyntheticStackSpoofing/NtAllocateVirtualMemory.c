#include "NtAllocateVirtualMemory.h"

uint64_t *ret[7] = {0};
uint64_t stacksize[7] = {0};
void *gadget;
DWORD status;

uint64_t *rsp;
uint64_t *old_rsp;
uint64_t *old_rbp;


void *FindUnwindInfo(void *hModule, void *lpProcVA)
{
    uintptr_t moduleAddr = (uintptr_t)hModule;
    uintptr_t procAddr = (uintptr_t)lpProcVA;

    uintptr_t functionRVA64 = procAddr - moduleAddr;
    unsigned long functionRVA = (unsigned long)functionRVA64;

    IMAGE_DOS_HEADER *dosHeader = (IMAGE_DOS_HEADER *)moduleAddr;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
        return NULL;

    IMAGE_NT_HEADERS64 *ntHeaders = (IMAGE_NT_HEADERS64 *)(moduleAddr + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
        return NULL;

    IMAGE_DATA_DIRECTORY exceptionDir = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION];
    unsigned long exceptionRVA = exceptionDir.VirtualAddress;
    unsigned long exceptionSize = exceptionDir.Size;

    if (exceptionRVA == 0 || exceptionSize == 0)
        return NULL;

    uintptr_t runtimeTable = moduleAddr + exceptionRVA;
    unsigned long count = exceptionSize / sizeof(IMAGE_RUNTIME_FUNCTION_ENTRY);

    for (unsigned long i = 0; i < count; i++)
    {
        unsigned long beginAddress = *(unsigned long *)(runtimeTable + i * 12 + 0);
        unsigned long endAddress = *(unsigned long *)(runtimeTable + i * 12 + 4);
        unsigned long unwindData = *(unsigned long *)(runtimeTable + i * 12 + 8);

        if (functionRVA >= beginAddress && functionRVA < endAddress)
        {
            return (void *)(moduleAddr + unwindData);
        }
    }

    return NULL;
}

unsigned long long GetFunctionStackFrameSize(void *unwindInfo)
{
    unsigned char *info = (unsigned char *)unwindInfo;

    unsigned char countOfCodes = info[2];
    unsigned char *unwindCodes = info + 4;

    unsigned long long stackSize = 0;

    for (unsigned char i = 0; i < countOfCodes; i++)
    {
        unsigned char unwindOp = unwindCodes[i * 2 + 1] & 0xF;
        unsigned char opInfo = (unwindCodes[i * 2 + 1] >> 4) & 0xF;

        if (unwindOp == UWOP_PUSH_NONVOL)
        {
            stackSize += 8;
        }
        else if (unwindOp == UWOP_ALLOC_SMALL)
        {
            stackSize += (opInfo * 8) + 8;
        }
        else if (unwindOp == UWOP_ALLOC_LARGE)
        {
            if (opInfo == 0)
            {
                unsigned short size = *(unsigned short *)(unwindCodes + (i + 1) * 2);
                stackSize += size * 8;
                i += 1;
            }
            else if (opInfo == 1)
            {
                unsigned long size = *(unsigned long *)(unwindCodes + (i + 1) * 2);
                stackSize += size;
                i += 2;
            }
        }
        else if (unwindOp == UWOP_SAVE_NONVOL || unwindOp == UWOP_SAVE_XMM128)
        {
            i += 1; // 1 extra slot for offset
        }
        else if (unwindOp == UWOP_SAVE_NONVOL_FAR || unwindOp == UWOP_SAVE_XMM128_FAR)
        {
            i += 2; // 2 extra slots for large offset
        }
    }

    return stackSize + 8;
}

void fillmyarray(uint64_t **ret, uint64_t *stacksize)
{
    HANDLE hModule = GetModuleHandle("ntdll.dll");
    HANDLE hProc = GetProcAddress(hModule, "LdrInitializeThunk");

    ret[6] = (uint64_t *)((uint8_t *)hProc + 0xE);
    ret[5] = (uint64_t *)((uint8_t *)hProc + 0x63);
    ret[4] = (uint64_t *)((uint8_t *)hProc + 0x1DB);

    hProc = GetProcAddress(hModule, "LdrInitShimEngineDynamic");
    ret[3] = (uint64_t *)((uint8_t *)hProc + 0x22E3);
    ret[2] = (uint64_t *)((uint8_t *)hProc + 0x3C3F);

    hProc = GetProcAddress(hModule, "RtlRegisterSecureMemoryCacheCallback");
    ret[1] = (uint64_t *)((uint8_t *)hProc + 0x14B1);

    hProc = GetProcAddress(hModule, "RtlCreateHeap");
    ret[0] = (uint64_t *)((uint8_t *)hProc + 0x8DA);
    for (uint8_t i = 0; i < 7; i++)
        stacksize[i] = GetFunctionStackFrameSize(FindUnwindInfo(hModule, ret[i]));
}

DWORD WINAPI SyscallThread(LPVOID param)
{

    __asm__ volatile(
        "mov %%rsp, %0\n\t"
        "mov %%rbp, %1\n\t"
        : "=r"(old_rsp), "=r"(old_rbp)
        :
        : "memory");

    rsp = (uint64_t *)((uintptr_t)old_rsp & 0xFFFFFFFFFFFFF000ULL);

    size_t total = 0;
    for (int i = 0; i < 7; i++)
        total += stacksize[i];
    // uncomment the following loop if you want to fill stack with 0.
    // for(int i = 0; i < total; i++){
    //     ((PBYTE)rsp)[i] = 0;
    // }
    uint64_t offset = 0;
    for (uint8_t i = 0; i < 7; i++)
    {
        *(uint64_t *)((uint8_t *)rsp + offset) = (uint64_t)ret[i];
        offset += stacksize[i];
    }
    __asm__ volatile(
        "mov %0, %%rsp\n\t"
        "jmp syscall\n\t" ::"r"(rsp));

    __asm__ volatile(
        ".global here\n\t"
        "here:\n\t"
        "mov %%eax, %0\n\t" // Graba the syscall status from EAX
        : "=r"(status));

    __asm__ volatile(
        "mov %0, %%rsp\n\t"
        "mov %1, %%rbp\n\t"
        :
        : "r"((uint64_t *)old_rsp), "r"((uint64_t *)old_rbp));
    return status;
}



