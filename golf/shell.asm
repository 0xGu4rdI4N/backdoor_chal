section .text
global _start

_start:
    ; syscall: execve("/bin/sh", ["/bin/sh"], NULL)
    xor eax, eax          ; Clear eax
    push eax              ; Null terminator for argv
    push 0x68732f2f      ; Push "//sh" (double slash for alignment)
    push 0x6e69622f      ; Push "/bin"
    mov ebx, esp         ; Pointer to "/bin//sh"
    push eax              ; Null terminator for envp
    push ebx             ; Pointer to argv
    mov ecx, esp         ; Pointer to argv
    mov al, 11           ; syscall number for execve
    int 0x80             ; Call kernel

    ; syscall: exit(0)
    xor ebx, ebx         ; Exit code 0
    mov eax, 1           ; syscall number for exit
    int 0x80             ; Call kernel