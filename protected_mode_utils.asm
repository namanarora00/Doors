; 32 bit Protected mode
[bits 32]

VIDEO_MEMORY equ 0xb8000   ; Every char displayed on the VGA device has 2 bytes. 1st byte is the ASCII code.
WHITE_ON_BLACK equ 0x0f     ; Second byte is it's attributes. (Colors, blinking or not)

; Display Device is memory mapped. Altering a memeory location will have corresponding changes
; Screen is represented as rows and columns. Memory mapped as 2d array.

; null terminated string in EBX
print_string_pm :
    pusha
    mov edx , VIDEO_MEMORY ; Set edx to the start of vid mem.

print_string_pm_loop :
    mov al, [ebx] 

    mov ah, WHITE_ON_BLACK ; Store the attributes in AH
    cmp al, 0 ; if (al == 0) , at end of string 
    je print_string_pm_done ; jump to done

    mov [edx], ax ; Store char and attributes at current
    add ebx, 1 ; Increment EBX to the next char in string.
    add edx, 2 ; Move to next character cell in vid mem.

    jmp print_string_pm_loop ; loop around to print the next char.

print_string_pm_done :
    popa
    ret 