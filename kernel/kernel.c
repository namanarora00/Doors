#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"

void main()
{
    clear_screen();
    print("Hello! Welcome to KANA OS!\n\0");
    idt_init();
    init_keyboard();
}