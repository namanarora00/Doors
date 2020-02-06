#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../drivers/low_level.h"

isr_t interrupt_handlers[256];

void print_ascii(int a)
{
    int len = 1;
    int n = a;

    while ((n = n / 10))
        len++;

    char out[len + 1];
    int i = len - 1;
    while (a)
    {
        char p = a % 10 + '0';
        out[i] = p;
        a /= 10;
        i--;
    }
    out[len] = '\0';
    print(out);
}

void isr_handler(registers_t registers)
{
    print("Interrupt received!: ");
    print_ascii(registers.int_no);
    print("\n");
}

extern void register_handler(int i, isr_t callback)
{
    interrupt_handlers[i] = callback;
}

void irq_handler(registers_t registers)
{
    if (registers.int_no >= 40)
    {
        // if the interrupt involves the slave PIC
        // send a reset signal to the slave
        out_byte_from_port(0x20, 0xA0);
    }
    // reset signal to master
    out_byte_from_port(0x20, 0x20);

    uint8 scancode = in_byte_from_port(0x60);

    isr_t handler = interrupt_handlers[registers.int_no];
    handler(registers);
}
