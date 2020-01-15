
// This function reads a byte from the specified port.

unsigned char in_byte_from_port(unsigned short port)
{
    unsigned char res;

    // Inline assembly:
    // Here the source and destination registers are written in opposite way.
    // "=a" (res) means take the value present in al and put it in the variable res
    // "d" (port) means take the value present in variable port and store it in the EDX register.
    // Format --> "instr" : "=register" (variable) : "register" (variable),

    // in instruction reads the port mapped to the address present in the dx register
    __asm__("in %%dx, %%al"
            : "=a"(res)
            : "d"(port));

    return res;
}

void out_byte_from_port(unsigned char data, unsigned short port)
{
    __asm__("out %%al, %%dx" ::"a"(data), "d"(port));
}

unsigned short in_word_from_port(unsigned short port)
{
    unsigned short res;

    __asm__("in %%dx , %%ax"
            : "=a"(res)
            : "d"(port));

    return res;
}

void out_word_from_port(unsigned short data, unsigned short port)
{
    __asm__("out %%ax, %%dx" ::"a"(data), "d"(port));
}

void memset(void *start, char target, int len)
{
    // Set byte by byte.
    unsigned char *ptr = start;

    while (len)
    {
        *ptr = target;
        len--;
        ptr++;
    }
}