print:
    ; requires starting address of the message to be in bx and string be null terminated
    pusha
    mov     ah, 0x0e

print_loop:
    mov     al, [bx]
    cmp     al, 0x0 ; checks for null char
    je      print_end 
    int     0x10
    inc     bx
    jmp     print_loop

print_end:
    popa
    ret


print_hex:
    ; number must be in dx
    pusha

    mov     cx, 0
    mov     ax, dx 
    mov     bx, hex_out

    add     bx, 5

hex_loop:
    cmp     cx, 4
    je      _print_hex
    and     ax, 0xf ; mask to get only the last 4 bytes
    cmp     ax, 0xa ; check if the value is less than 10
    jl      set
    add     ax, 0x27 ; letters start at 0x61
    jl      set

set:
    add     al, 0x30
    mov     byte [bx], al   ; set byte to the char in al
    inc     cx
    dec     bx
    shr     dx, 4   ; shift 4 bits i.e 1 digit in hex
    mov     ax, dx
    jmp     hex_loop

_print_hex:
    mov     bx, hex_out
    call    print
    popa
    ret


; data

hex_out:  db '0x0000', 0
