#include "../drivers/screen.h"
#include "../cpu/idt.h"

void main()
{
    clear_screen();
    idt_init();

    char *message = "Hello! Welcome to KANA OS!\n\0";
    print(message);

    __asm__ volatile("int $0x1F");
}