/** @file : keyboard.c
 *  @brief: This module implements APIs for the keyboard driver.
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

#include <stdint.h>
#include "../drivers/screen.h"
#include "../drivers/ports.h"
#include "../libc/function.h"
#include "../cpu/isr.h"
#include "keyboard.h"
#include "screen.h"

/* Macros for Non-Printable keys indicating their scancodes. */
#define ESC             0x00 // "Escape" button.
#define ENTER           0x1c // "Enter" button.
#define LCNTRL          0x1d // Left "Control"
#define LSHIFT          0x2a // Left "Shift"
#define RSHIFT          0x36 // Right "Shift"
#define LALT            0x38 // Left "Alt".
#define CAPSLOCK        0x3a // "Capslock" button.
#define NUMLOCK         0x45 // "Numlock" button.
#define SCROLLOCK       0x46 // "ScrollLock" button.
#define KHOME           0x47 // Keypad "Home" button.
#define KUP             0x48 // Keypad "Up Arrow" button.
#define KPGUP           0x49 // Keypad "Page Up" button.
#define KLEFT           0x4b // Keypad "Left Arrow" button.
#define KRIGHT          0x4d // Keypad "Right Arrow" button.
#define KEND            0x4f // Keypad "End" button.
#define KDOWN           0x50 // Keypad "Down Arrow" button.
#define KPGDN           0x51 // Keypad "Page Down" button.
#define KINSERT         0x52 // Keypad "Insert" button.
#define KDEL            0x53 // Keypad "Delete" button.



static void keyboard_callback(register_t reg);
static void scancode_handler(uint8_t scancode);

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}

static void keyboard_callback(register_t reg)
{
    UNUSED(reg); // To suppress the -Wunused-parameter warning.
    uint8_t scancode = port_byte_in(0x60);
    scancode_handler(scancode);
}

/* A helper function for keyboard callback. */
static void scancode_handler(uint8_t scancode)
{
	static int shift = 0;
	static int numlock = 0;
	static int capslock = 0;
	int offset;

    /* A standard US keyboard layout with 0x58 keys.
	 * The character '?' represents non-printable keys. */
    char *keyboard_layout =
            "????1!2@3#4$5%6^7&8*9(0)-_=+\b\b\t\tqQwWeErRtTyYuUiIoOpP[{]}????"
            "aAsSdDfFgGhHjJkKlL;:'\"`~??\\|zZxXcCvVbBnNmM,<.>/???**??  ??F1"
            "F2F3F4F5F6F7F8F9Fa?????7?8?9--?455?6++?1?2?3?0?.????FbFc";

	switch(scancode) {
	case LSHIFT:
	case RSHIFT:
		shift = 1;
		return;
	case LSHIFT + 0x80:
	case RSHIFT + 0x80:
		shift = 0;
		return;
	case ENTER:
		print("\n");
		return;
	case CAPSLOCK:
		capslock = !capslock;
		return;
	case NUMLOCK:
		numlock = !numlock;
		return;
	case KHOME:
	case KUP:
	case KPGUP:
	case KLEFT:
	case KRIGHT:
	case KEND:
	case KDOWN:
	case KPGDN:
	case KINSERT:
	case KDEL:
		if (numlock)
			break;
	case ESC:
	case LCNTRL:
	case LALT:
	case SCROLLOCK:
		return;
	}

	if (scancode > 0x58)
		return;

	offset = (int)scancode * 2;

	if (shift && scancode < 0x37 && !capslock)
		offset++;
	if (capslock && keyboard_layout[offset] > 96
		&& keyboard_layout[offset] < 123 && !shift)
		offset++;
	if (numlock && scancode > 0x46 && scancode < 0x53)
		offset++;

    char letter = keyboard_layout[offset];
    char str[2] = {letter, '\0'};
    print(str);
}
