/** @file : kernel.c
 *  @brief: This module supplies the kernel functions for the operating
 * 			system.
 *
 *  Copyright (C) 2020  Suraj Upadhyay
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

#include "../drivers/screen.h"

void kernel_main(void)
{
	int i;
	clear_screen();
	for (i = 0; i < 25; i++)
		print("MrSquanchee\n");
}
