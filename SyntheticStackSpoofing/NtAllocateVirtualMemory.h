#ifndef SYSCALL_H
#define SYSCALL_H

#include <windows.h>
#include <stdint.h>

// ====================================================================
#define UWOP_PUSH_NONVOL 0
#define UWOP_ALLOC_LARGE 1
#define UWOP_ALLOC_SMALL 2
#define UWOP_SET_FPREG 3
#define UWOP_SAVE_NONVOL 4
#define UWOP_SAVE_NONVOL_FAR 5
#define UWOP_SAVE_XMM128 8
#define UWOP_SAVE_XMM128_FAR 9
#define UWOP_PUSH_MACHFRAME 10
// ====================================================================

// ====================================================================
void *FindUnwindInfo(void *hModule, void *lpProcVA); // returns the handle to stack frame size info from .pdata section.

unsigned long long GetFunctionStackFrameSize(void *unwindInfo); // returns stacksize+8

void fillmyarray(uint64_t **ret, uint64_t *stacksize); // it fills the array of return addresses which will be placed in stack for spoofing.

DWORD WINAPI SyscallThread(LPVOID param); // in case if it crashes our main thread should keep executing. an exception handler should be implemented to catch exceptions. current call chain is good, syscall executes and returns the status code in eax register. there is a return gadget at the end of the RtlCreateHeap which returns the execution to Syscall Thread Function which then safely retrives the status code and exits. so no exceptions occur at this point.

#endif
