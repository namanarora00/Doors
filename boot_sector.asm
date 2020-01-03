[org 0x7c00]
; sets assembler location counter to 0x7C00 (address where BIOS loads this program)
; An alternative to the above approach will be to set Data segment to 0x7c0.

KERNEL_OFFSET equ 0x1000    ; memeory offset at which we will load the kernel from the disk.

[bits 16]

jmp main

; Real mode includes
%include "print_utils.asm"
%include "disk_utils.asm"

main:
    mov bp, 0x9000      ; making stack far away. 
    mov sp, bp

    mov bx, in_real_mode_msg
    call print

    call load_kernel

    call switch_to_protected_mode

    jmp $

load_kernel:
    mov bx, load_kernel_msg
    call print

    mov bx, KERNEL_OFFSET   ; Params for disk load. We load 15 sectors (dh) from drive dl to bx offset in the memory.
    mov dh, 15
    mov dl, [BOOT_DRIVE]

    call disk_load

    mov bx, success
    call print

    ret

switch_to_protected_mode:
    cli ; disable interrupts
    
    lgdt [gdt_descriptor]   ; load GDT
    
    mov eax, cr0    ; set cr0 indirectly
    or eax, 0x1
    mov cr0, eax    ; control register's first bit set to 1

    jmp CODE_SEG:init_pm    ; far jump. Induces a flush in the pipeline.

[bits 32]

; Protected mode includes
%include "protected_mode_utils.asm"
%include "gdt.asm"


init_pm:
    mov ax, DATA_SEG    
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call BEGIN_PM


BEGIN_PM:
    mov ebx, in_protected_mode_msg
    call print_string_pm

    call KERNEL_OFFSET

    jmp $

; data

BOOT_DRIVE: db 0
in_real_mode_msg: db 'In real Mode', 0
in_protected_mode_msg: db 'In protected Mode', 0
load_kernel_msg: db 'Loading kernel from disk', 0
success: db 'Loaded Kernel', 0

; Magic number and offset

times 510-($-$$) db 0
dw 0xaa55
