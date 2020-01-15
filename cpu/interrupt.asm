[GLOBAL idt_flush]

idt_flush:
    mov eax, [esp + 4] ; load the idt_ptr's address which was passed as an argument.
    lidt [eax]  ; load idt
    ret
    
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
ISR_NOERRORCODE 8
ISR_NOERRORCODE 9
ISR_NOERRORCODE 10
ISR_NOERRORCODE 11
ISR_NOERRORCODE 12
ISR_NOERRORCODE 13
ISR_NOERRORCODE 14
ISR_NOERRORCODE 15
ISR_NOERRORCODE 16
ISR_NOERRORCODE 17
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
