#include <windows.h>
#include <stdio.h>

int main(void)
{
    HANDLE hThread = GetCurrentThread();
    CONTEXT ctx;

#ifdef _M_X64
    ctx.ContextFlags = CONTEXT_FULL | CONTEXT_DEBUG_REGISTERS;
#else
    ctx.ContextFlags = CONTEXT_FULL | CONTEXT_DEBUG_REGISTERS;
#endif

    if (!GetThreadContext(hThread, &ctx)) {
        printf("GetThreadContext failed. Error: %lu\n", GetLastError());
        return 1;
    }

#ifdef _M_X64
    printf("---- x64 CONTEXT ----\n");
    printf("Rax: 0x%llX\nRbx: 0x%llX\nRcx: 0x%llX\nRdx: 0x%llX\n", ctx.Rax, ctx.Rbx, ctx.Rcx, ctx.Rdx);
    printf("Rsi: 0x%llX\nRdi: 0x%llX\nRbp: 0x%llX\nRsp: 0x%llX\nRip: 0x%llX\n", ctx.Rsi, ctx.Rdi, ctx.Rbp, ctx.Rsp, ctx.Rip);
    printf("R8 : 0x%llX\nR9 : 0x%llX\nR10: 0x%llX\nR11: 0x%llX\n", ctx.R8, ctx.R9, ctx.R10, ctx.R11);
    printf("R12: 0x%llX\nR13: 0x%llX\nR14: 0x%llX\nR15: 0x%llX\n", ctx.R12, ctx.R13, ctx.R14, ctx.R15);
    printf("EFlags: 0x%llX\n", ctx.EFlags);

    printf("Segment Registers: CS=0x%X DS=0x%X ES=0x%X FS=0x%X GS=0x%X SS=0x%X\n",
           ctx.SegCs, ctx.SegDs, ctx.SegEs, ctx.SegFs, ctx.SegGs, ctx.SegSs);

    printf("Debug Registers: Dr0=0x%llX Dr1=0x%llX Dr2=0x%llX Dr3=0x%llX\n",
           ctx.Dr0, ctx.Dr1, ctx.Dr2, ctx.Dr3);
    printf("Dr6=0x%llX Dr7=0x%llX\n", ctx.Dr6, ctx.Dr7);

#else
    printf("---- x86 CONTEXT ----\n");
    printf("Eax=0x%X Ebx=0x%X Ecx=0x%X Edx=0x%X\n", ctx.Eax, ctx.Ebx, ctx.Ecx, ctx.Edx);
    printf("Esi=0x%X Edi=0x%X Ebp=0x%X Esp=0x%X Eip=0x%X\n", ctx.Esi, ctx.Edi, ctx.Ebp, ctx.Esp, ctx.Eip);
    printf("EFlags=0x%X\n", ctx.EFlags);
    printf("Segment Registers: CS=0x%X DS=0x%X ES=0x%X FS=0x%X GS=0x%X SS=0x%X\n",
           ctx.SegCs, ctx.SegDs, ctx.SegEs, ctx.SegFs, ctx.SegGs, ctx.SegSs);
    printf("Debug Registers: Dr0=0x%X Dr1=0x%X Dr2=0x%X Dr3=0x%X\n", ctx.Dr0, ctx.Dr1, ctx.Dr2, ctx.Dr3);
    printf("Dr6=0x%X Dr7=0x%X\n", ctx.Dr6, ctx.Dr7);
#endif

    // Optionally, you can print Floating Point/XMM registers if needed

    return 0;
}
