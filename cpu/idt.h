#ifndef IDT_H
#define IDT_H

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

extern void idt_flush(uint32);
extern void idt_init();
static void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags);

// Interrupt gate (entry in the idt)
struct idt_entry_struct
{
    uint16 base_lo; // lower 16 bits of the base
    uint16 sel;     // kernel segment selectror
    uint8 always0;  // always 0
    uint8 flags;    // flags
    uint16 base_hi; // higher 16 bits of the base
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct
{
    uint16 limit; // size of the idt - 1
    uint32 base;  // address of the first gate in the idt
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif