#include "../drivers/screen.h"

void main()
{
    clear_screen();

    char *message = "Hello! Welcome to KANA OS!\0";
    print(message);
}