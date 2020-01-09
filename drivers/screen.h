#define VIDEO_MEMORY 0xb8000
#define ROWS 25
#define COLS 80

#define WHITE_ON_BLACK 0x0f

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

int screen_offset(int row, int col);
void print_char(char c, int row, int col, char attr);
int cursor_offset();
void set_cursor(int offset);
void clear_screen();
void print(char *text);
