; This piece of code makes a jump to the main function in kernel code. When loading the kernel there may be 
; other routines which will precede the main function and may be called. This code is linked with the kernel code and 
; executes before the kernel code.

[bits 32]

[extern main] ; Using this, we declare that we'll be using an externel label which is present in the other object file.

call main   ; call the main function

jmp $