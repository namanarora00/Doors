
#include "screen.h"
#include "low_level.h"

int screen_offset(int row, int col)
{
    return (row * COLS + col) * 2;
}

void print_char(char c, int row, int col, char attr)
{
    unsigned char *video = (char *)VIDEO_MEMORY;

    // handling the default case
    if (!attr)
        attr = WHITE_ON_BLACK;

    int offset;

    if (col == -1 && row == -1)
        offset = cursor_offset();
    else
        offset = screen_offset(row, col);

    // If it is a new line char, we only change the cursor pos by changing the offset.
    if (c == '\n')
    {
        int current_row = offset / 2 * COLS;        // using the formula in screen offset function.
        offset = screen_offset(current_row + 1, 0); // make the offset to the next row's first column
    }
    else
    {
        video[offset] = c;
        video[offset + 1] = attr;

        // shift to the next character cell
        offset += 2;
    }

    set_cursor(offset);
}

int cursor_offset()
{
    int offset;

    out_byte_from_port(14, REG_SCREEN_CTRL); // write 14 to control register to get the higher byte
    offset = in_byte_from_port(REG_SCREEN_DATA) << 8;

    out_byte_from_port(15, REG_SCREEN_CTRL); // Write 15 to control register to get the lower byte
    offset += in_byte_from_port(REG_SCREEN_DATA);

    //  We change it to number of char cells
    // offset returned by the VGA device is in terms of number of characters.
    return offset * 2;
}

void set_cursor(int offset)
{
    offset = offset / 2; // since we're writing, we divide it by two to make it in terms of no. of chars opposed to char cells

    out_byte_from_port(14, REG_SCREEN_CTRL);                           // set byte in the control register.
    out_byte_from_port((unsigned char)(offset >> 8), REG_SCREEN_DATA); // set the data in the data register to update cursor location. (higher byte)
    out_byte_from_port(15, REG_SCREEN_CTRL);
    out_byte_from_port((unsigned char)(offset & (0xff)), REG_SCREEN_DATA); // lower byte
}

void clear_screen()
{
    unsigned char *video = (char *)VIDEO_MEMORY;
    int current_row = 0;

    while (current_row < ROWS)
    {
        int current_col = 0;

        while (current_col < COLS)
        {
            char blank = ' ';
            print_char(blank, current_row, current_col, WHITE_ON_BLACK);
            current_col += 1;
        }

        current_row++;
    }

    int top_left = screen_offset(0, 0);
    set_cursor(top_left);
}

void print(char *text)
{
    while (*text)
    {
        print_char(*text, -1, -1, 0);
        text++;
    }
}