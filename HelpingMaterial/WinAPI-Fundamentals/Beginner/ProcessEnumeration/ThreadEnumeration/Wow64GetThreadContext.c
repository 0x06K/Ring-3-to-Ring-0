#include <windows.h>
#include <stdio.h>

int main(void)
{
    HANDLE hThread = GetCurrentThread(); // Current thread
    WOW64_CONTEXT ctx;

    // Request full context
    ctx.ContextFlags = CONTEXT_FULL;

    if (!Wow64GetThreadContext(hThread, &ctx)) {
        printf("Wow64GetThreadContext failed. Error: %lu\n", GetLastError());
        return 1;
    }

    printf("---- WOW64 (x86) CONTEXT ----\n");
    printf("Eax=0x%X Ebx=0x%X Ecx=0x%X Edx=0x%X\n", ctx.Eax, ctx.Ebx, ctx.Ecx, ctx.Edx);
    printf("Esi=0x%X Edi=0x%X Ebp=0x%X Esp=0x%X Eip=0x%X\n", ctx.Esi, ctx.Edi, ctx.Ebp, ctx.Esp, ctx.Eip);
    printf("EFlags=0x%X\n", ctx.EFlags);
    printf("Segment Registers: CS=0x%X DS=0x%X ES=0x%X FS=0x%X GS=0x%X SS=0x%X\n",
           ctx.SegCs, ctx.SegDs, ctx.SegEs, ctx.SegFs, ctx.SegGs, ctx.SegSs);
    printf("Debug Registers: Dr0=0x%X Dr1=0x%X Dr2=0x%X Dr3=0x%X\n", ctx.Dr0, ctx.Dr1, ctx.Dr2, ctx.Dr3);
    printf("Dr6=0x%X Dr7=0x%X\n", ctx.Dr6, ctx.Dr7);

    return 0;
}
