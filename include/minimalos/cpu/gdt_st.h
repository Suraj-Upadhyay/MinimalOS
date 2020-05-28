/** @file : gdt_st.h
 *  @brief: This module provides data structures for Global Descriptor Table.
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

#ifndef GDT_ST_H
#define GDT_ST_H

#include <stdint.h>

struct gdt_entry_struct {
	uint16_t size_low;		// Lower 16 bits of size limit.
	uint16_t base_low;	 	// Lower 16 bits of base address.
	uint8_t base_mid;		// Next 8 bits of base address.
	uint8_t access_flags;	// 8 bits of Access flags.
					        // Type : 5, DT : 1, DPL : 1, P : 1.
	uint8_t granularity;
	uint8_t base_high;		// Next 8 bits of base address.
}__attribute__((packed));

struct gdt_register_struct {
	uint16_t size;			// Size of the descriptor table.
	uint32_t base_addr;		// Base address of the descriptor table.
}__attribute__((packed));

// Type define all the names to sensible and shorter alternatives.
typedef struct gdt_entry_struct gdt_entry_t;
typedef struct gdt_register_struct gdt_register_t;

#endif /* !defined(GDT_ST_H). */
