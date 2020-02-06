%macro ISR_NOERRORCODE 1
    [GLOBAL isr%1]
    isr%1:
        cli 
        push byte 0 ; dummy error code if not pushed by the interrupt. 8, 10-14 push an error code.
        push byte %1    ; interrupt number
        jmp isr_common_stub ; common interrupt handler. 
%endmacro

; Macro when error code is not required to be pushed on the stack
%macro ISR_ERRCODE 1
    [GLOBAL isr%1]
    isr%1:
        cli 
        push byte %1    ; interrupt number
        jmp isr_common_stub ; common interrupt handler. 
%endmacro

ISR_NOERRORCODE 0
ISR_NOERRORCODE 1
ISR_NOERRORCODE 2
ISR_NOERRORCODE 3
ISR_NOERRORCODE 4
ISR_NOERRORCODE 5
ISR_NOERRORCODE 6
ISR_NOERRORCODE 7
ISR_ERRCODE 8
ISR_NOERRORCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRORCODE 15
ISR_NOERRORCODE 16
ISR_ERRCODE 17
ISR_NOERRORCODE 18
ISR_NOERRORCODE 19
ISR_NOERRORCODE 20
ISR_NOERRORCODE 21
ISR_NOERRORCODE 22
ISR_NOERRORCODE 23
ISR_NOERRORCODE 24
ISR_NOERRORCODE 25
ISR_NOERRORCODE 26
ISR_NOERRORCODE 27
ISR_NOERRORCODE 28
ISR_NOERRORCODE 29
ISR_NOERRORCODE 30
ISR_NOERRORCODE 31

[EXTERN isr_handler]



isr_common_stub:
    pusha

    mov ax, ds
    push eax

    ; loads data segment of the kernel (gdt 0x10). Not reqd now.
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8  ; cleans pushed error code and isr number
    sti     ; sets interrupt flag
    iret    ; return


[EXTERN irq_handler]

irq_common_stub:
    pusha

    mov ax, ds
    push eax

    ; loads data segment of the kernel (gdt 0x10). Not reqd now.
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler

    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa
    add esp, 8  ; cleans pushed error code and isr number
    sti     ; sets interrupt flag
    iret    ; return


%macro IRQ 2
  global irq%1
  irq%1:
    cli
    push byte %1     ; dummy error code
    push byte %2    ; maps to this interrupt
    jmp irq_common_stub
%endmacro

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47