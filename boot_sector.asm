; Bootloader

[org 0x7c00]    ; sets assembler location counter to 0x7C00 (address where BIOS loads this program)

jmp main

print:
    ; requires starting address of the message to be in bx and string be null terminated
    pusha
    mov al, [bx]

    loop:
        cmp byte [bx], 0x00 ; checks for null char
        je end 
        mov al, [bx]
        int 0x10
        inc bx

        jmp loop
    end:

    popa
    ret

message: db 'Hello, Naman', 0


main:
    mov ah, 0x0e
    mov bx, message
    call print
    
jmp $
times 510-($-$$) db 0
dw 0xaa55                  
