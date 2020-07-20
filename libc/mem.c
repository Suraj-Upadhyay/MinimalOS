/** @file : mem.c
 *  @brief: This module implements memory utility functions.
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

#include "minimalos/libc/mem.h"

int mem_cpy(char *dest, char *src, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		*(dest + i) = *(src + i);
	}
	return i;
}

void *memset(void *dest, char c, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		*((char *)dest + i) = c;
	}
	return dest;
}
