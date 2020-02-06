#include "idt.h"
#include "../drivers/low_level.h"

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

extern void idt_init()
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1; // size of all the entries - 1
    idt_ptr.base = (uint32)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

    idt_set_gate(0, (uint32)isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint32)isr1, 0x08, 0x8E);
    idt_set_gate(2, (uint32)isr2, 0x08, 0x8E);
    idt_set_gate(3, (uint32)isr3, 0x08, 0x8E);
    idt_set_gate(4, (uint32)isr4, 0x08, 0x8E);
    idt_set_gate(5, (uint32)isr5, 0x08, 0x8E);
    idt_set_gate(6, (uint32)isr6, 0x08, 0x8E);
    idt_set_gate(7, (uint32)isr7, 0x08, 0x8E);
    idt_set_gate(8, (uint32)isr8, 0x08, 0x8E);
    idt_set_gate(9, (uint32)isr9, 0x08, 0x8E);
    idt_set_gate(10, (uint32)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint32)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint32)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint32)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint32)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint32)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint32)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint32)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint32)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint32)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint32)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint32)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint32)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint32)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint32)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint32)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint32)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint32)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint32)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint32)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint32)isr31, 0x08, 0x8E);

    // PIC
    // Master: Control = 0x20; Data = 0x21
    // Slave: Control = 0xA0; Data = 0xA1

    out_byte_from_port(0x11, 0x20);
    out_byte_from_port(0x11, 0xA0);
    out_byte_from_port(0x20, 0x21);
    out_byte_from_port(0x28, 0xA1);
    out_byte_from_port(0x00, 0x21);
    out_byte_from_port(0x00, 0xA1);
    out_byte_from_port(0x01, 0x21);
    out_byte_from_port(0x01, 0xA1);
    out_byte_from_port(0xff, 0x21);
    out_byte_from_port(0xff, 0xA1);

    idt_set_gate(32, (uint32)(irq0), 0x08, 0x8E);
    idt_set_gate(33, (uint32)(irq1), 0x08, 0x8E);
    idt_set_gate(34, (uint32)(irq2), 0x08, 0x8E);
    idt_set_gate(35, (uint32)(irq3), 0x08, 0x8E);
    idt_set_gate(36, (uint32)(irq4), 0x08, 0x8E);
    idt_set_gate(37, (uint32)(irq5), 0x08, 0x8E);
    idt_set_gate(38, (uint32)(irq6), 0x08, 0x8E);
    idt_set_gate(39, (uint32)(irq7), 0x08, 0x8E);
    idt_set_gate(40, (uint32)(irq8), 0x08, 0x8E);
    idt_set_gate(41, (uint32)(irq9), 0x08, 0x8E);
    idt_set_gate(42, (uint32)(irq10), 0x08, 0x8E);
    idt_set_gate(43, (uint32)(irq11), 0x08, 0x8E);
    idt_set_gate(44, (uint32)(irq12), 0x08, 0x8E);
    idt_set_gate(45, (uint32)(irq13), 0x08, 0x8E);
    idt_set_gate(46, (uint32)(irq14), 0x08, 0x8E);
    idt_set_gate(47, (uint32)(irq15), 0x08, 0x8E);

    __asm__ __volatile__("lidtl (%0)"
                         :
                         : "r"(&idt_ptr));
    __asm__ __volatile__("sti");
}

static void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags)
{
    idt_entries[num].base_lo = base & 0xffff;
    idt_entries[num].base_hi = (base >> 16) & 0xffff; // lower bits
    idt_entries[num].always0 = 0;
    idt_entries[num].sel = sel;
    idt_entries[num].flags = flags; // here the ring level is set to 0 i.e kernel mode. When using user mode it should be set to 3. i.e OR with 0x60
}