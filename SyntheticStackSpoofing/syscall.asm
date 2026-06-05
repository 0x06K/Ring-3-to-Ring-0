global baseAddress
global regionSize

section .data
    baseAddress dq 0
    regionSize  dq 4096

section .text

extern here
extern gadget
global syscall
syscall:
    ; set up stack for args 5 & 6

    ; arg5 = AllocationType (MEM_COMMIT | MEM_RESERVE = 0x3000)
    mov rax, 0x3000
    mov [rsp+0x28], rax

    ; arg6 = Protect (PAGE_EXECUTE_READWRITE = 0x40)
    mov rax, 0x40
    mov [rsp+0x30], rax

    ; arg1 = ProcessHandle (-1 = current process)
    mov rcx, -1

    ; arg2 = &baseAddress
    lea rdx, [rel baseAddress]

    ; arg3 = ZeroBits
    xor r8, r8

    ; arg4 = &regionSize
    lea r9, [rel regionSize]
    
    lea rax, [rel here]
    mov [rsp+0x270], rax    ; return address for our ret gadget
    
    mov rax, [rel gadget]   ; 1. Load the 64-bit base address of 'args' into RAX

    jmp rax

    

