#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"

void print_ascii(int a)
{
    char *out = "00";
    int i = 1;
    int n = a;
    while (a)
    {
        char p = a % 10 + '0';
        out[i] = p;
        a /= 10;
        i--;
    }
    print(out);
}

void isr_handler(registers_t registers)
{
    print("Interrupt received!: ");
    print_ascii(registers.int_no);
    print("\n");
}