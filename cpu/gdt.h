/** @file : dt.c
 *  @brief: This module declares global descriptor table's initialization and its
 *          helper functions.
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

#ifndef GDT_H
#define GDT_H

#include <stdint.h>

/* GDT Initialization functions. */
/* gdt_flush is defined in assembly. */
extern void gdt_flush(uint32_t);
void init_gdt(void);
void set_gdt_gate(int32_t index, uint32_t base, uint32_t size,
			 	  uint8_t flags, uint8_t granularity);

#endif /* !defined(GDT_H). */
