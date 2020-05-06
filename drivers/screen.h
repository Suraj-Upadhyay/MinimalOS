#ifndef SCREEN_H
#define SCREEN_H

/* In text VGA mode the memory address mapped to the screen device starts
 * at 0xb8000.
 */
#define VIDEO_MEMORY_ADDRESS 0xb8000
/* The control I/O port register for screen driver. */
#define REG_SCREEN_CNTRL 0x3d4
/* The data I/O port register for screen driver. */
#define REG_SCREEN_DATA 0x3d5

/* Currently the available maximum screen size for our OS is 25x85. */
#define MAX_ROWS 25
#define MAX_COLS 80

/* The codes are interpreted as 0x[bg][fg] where bg and fg are background and
 * and foreground respectively and both can take on values representing colors
 * as : 0 = Black, 1 = Blue, 2 = Green, 3 = Aqua, 4 = Red, 5 = Purple,
 * 6 = Yellow, 7 = White, 8 = Grey, 9 = Light Blue, A = Light Green,
 * B = Light Aqua, C = Light Red, D = Light Purple, E = Light Yellow,
 * and F = Bright White.
 */
#define WHITE_ON_BLACK 0x0f     // For normal texts.
#define RED_ON_BLACK 0x04       // For errors.
#define GREEN_ON_BLACK 0x02     // For Successes.

/* Clear the whole screen. */
void clear_screen(void);

/* Functions to write normal text to the screen.
 * That is with WHITE_ON_BLACK.
 */
void print_at(char *message, int row, int col);
void print(char *message);

/* Functions to write color attributed text to the screen.
 * That is with WHITE_ON_BLACK.
 */
void kprint_at(char *message, int row, int col, int color_attr);
void kprint(char *message, int color_attr);

/* Functions to write helpful runtime debugging information to the screen. */
void debug_success_msg_at(char *message, int row, int col);
void debug_success_msg(char *message);
void debug_error_msg_at(char *message, int row, int col);
void debug_error_msg(char *message);

#ifdef PRIVATE_SCREEN_H
/* Functions to get and set offset. */
int get_cursor(void);
void set_cursor(int offset);
int get_offset_from_dim(int row, int col);
/* Prints a single character at col and row. */
void print_char(unsigned char ch, int row, int col, int color_attr);
#endif /* define PRIVATE_SCREEN_H. */

#endif /* define SCREEN_H. */
