/** @file : screen.c
 *  @brief: This module implements APIs for the screen driver.
 *
 *  Copyright (C) 2020  Suraj Upadhyay <usuraj35@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 **/

#define PRIVATE_SCREEN_H
#include <stdint.h>
#include "screen.h"
#include "ports.h"
#include "../libc/mem.h"

// Define functions private to screen.h for internal use.

/* Gets the screen offset i.e. the cursor position in video memory. */
int get_cursor(void)
{
	int offset;

	/* The high byte is retreived with 14. */
	port_byte_out(REG_SCREEN_CNTRL, 14);
	offset = port_byte_in(REG_SCREEN_DATA) << 8;
	/* The lower byte is retreived with 15. */
	port_byte_out(REG_SCREEN_CNTRL, 15);
	offset = offset + port_byte_in(REG_SCREEN_DATA);

	return offset * 2;
}

/* Sets the screen offset i.e. the cursor position in video memory. */
void set_cursor(int offset)
{
	offset /= 2;
	port_byte_out(REG_SCREEN_CNTRL, 14);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	port_byte_out(REG_SCREEN_CNTRL, 15);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_offset_from_dim(int row, int col)
{
	return (row * MAX_COLS + col) * 2;
}

int scroll(int offset)
{
	int i;
	char *video_memory = (char *) VIDEO_MEMORY_ADDRESS;

	if (offset < MAX_ROWS * MAX_COLS * 2)
		return offset;

	for (i = 0; i < MAX_ROWS - 1; i++)
		mem_cpy(video_memory + 2 * i * MAX_COLS,
				video_memory + 2 * (i + 1) * MAX_COLS,
				2 * MAX_COLS);

	offset = get_offset_from_dim(24, 0);
	for (i = 0; i < MAX_COLS; i++) {
		video_memory[offset++] = ' ';
		video_memory[offset++] = WHITE_ON_BLACK;
	}

	return get_offset_from_dim(24, 0);
}

/* Print a single character at a time at the cell [row, col]. */
void print_char(unsigned char ch, int row, int col, int color_attr)
{
	char *video_memory = (char *) VIDEO_MEMORY_ADDRESS;
	int offset;

	if (row >= MAX_ROWS || col >= MAX_COLS) {
		offset = get_offset_from_dim(24, 79);
		video_memory[offset++] = 'X';
		video_memory[offset] = RED_ON_BLACK;
		return;
	}

	if (!color_attr)
		color_attr = WHITE_ON_BLACK;
	if (row >= 0 && col >= 0)
		offset = get_offset_from_dim(row, col);
	else
		offset = get_cursor();

	if (ch == '\n') {
		row = offset / (2 * MAX_COLS);
		offset = get_offset_from_dim(row + 1, 0);
	} else if (ch == '\b') {
		if (offset < 1)
			return;
		video_memory[--offset] = WHITE_ON_BLACK;
		video_memory[--offset] = '\0';
	} else {
		video_memory[offset] = ch;
		video_memory[offset + 1] = color_attr;
		offset += 2;
	}

	offset = scroll(offset);
	set_cursor(offset);
}

// Define the screen.h interface functions.

/* Print message at specified position. */
void kprint_at(char *message, int row, int col, int color_attr)
{
	int offset, i;

	if (row >= MAX_ROWS || col >= MAX_COLS)
		return;
	if (row >= 0 && col >= 0)
		offset = get_offset_from_dim(row, col);
	else
		offset = get_cursor();

	set_cursor(offset);

	for (i = 0; message[i]; i++)
		print_char(message[i], -1, -1, color_attr);
}

/* Print message at current cursor position. */
void kprint(char *message, int color_attr)
{
	kprint_at(message, -1, -1, color_attr);
}

void print_at(char *message, int row, int col)
{
	kprint_at(message, row, col, WHITE_ON_BLACK);
}

void print(char *message)
{
	kprint(message, WHITE_ON_BLACK);
}

void print_hex(uint32_t hex)
{
	char *std_hex = "0x00000000";
	int ch, iter = 8;

	if (hex == 0) {
		print("0x0");
		return;
	}

	/* Copy the characters to the standard hexadecimal format
	 * one by one with Least Significant Digits copied first. */
	while (hex) {
		/* Retreive LSD. */
		ch = hex & 0x0000000f;
		if (ch < 10)
			ch += 48;	/* Numeric conversion. */
		else
			ch += 87;	/* Alphabetical conversion. */
		std_hex[iter + 1] = ch;
		iter--;
		hex = hex >> 4;
	}
	/* Eliminate insignificant zeroes. */
	int preceding_zeroes = 0;
	iter = 2;
	while (std_hex[iter++] == '0')
		preceding_zeroes++;
	std_hex[preceding_zeroes] = '0';
	std_hex[preceding_zeroes + 1] = 'x';

	print(std_hex + preceding_zeroes);
	// Cleanup the memory space for std_hex.
	iter = 0;
	while (iter < 10)
		std_hex[iter++] = '0';
	std_hex[1] = 'x';
}

void print_dec(uint32_t dec)
{
	// Number of digits in largest 32-bit decimal number.
	char *std_dec = "0000000000";
	uint8_t digit, iter = 9, leading_zeroes = 0;

	if (dec == 0) {
		print("0");
		return;
	}

	/* Copy the Least Significat Digits one by one
	 * into the standard decimal format. */
	while (dec) {
		digit = dec % 10;
		digit += 48;
		std_dec[iter--] = digit;
		dec = dec / 10;
	}

	/* Eliminate leading zeroes. */
	while (std_dec[leading_zeroes] == '0')
		leading_zeroes++;

	print(std_dec + leading_zeroes);

	// Cleanup the memory space for std_dec.
	iter = 0;
	while (iter < 10)
		std_dec[iter++] = '0';
}

/* Functions to print debug information. */
void debug_success_msg_at(char *message, int row, int col)
{
	kprint_at(message, row, col, GREEN_ON_BLACK);
}

void debug_success_msg(char *message)
{
	kprint(message, GREEN_ON_BLACK);
}

void debug_error_msg_at(char *message, int row, int col)
{
	kprint_at(message, row, col, RED_ON_BLACK);
}

void debug_error_msg(char *message)
{
	kprint(message, RED_ON_BLACK);
}

/* Clear the screen i.e. effectively print spaces all over the screen. */
void clear_screen(void)
{
	int i, j;
	for (i = 0; i < MAX_ROWS; i++) {
		for (j = 0; j < MAX_COLS; j++) {
			print_char(' ', i, j, 0);
		}
	}
	set_cursor(0);
}
