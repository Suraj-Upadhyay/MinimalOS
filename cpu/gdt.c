/** @file : dt.c
 *  @brief: This module defines functions which initialize the Global
 * 			Descriptor Table.
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
#include "gdt_st.h"
#include "gdt.h"

// GDT Data Structures.
gdt_entry_t gdt_entries[5];
gdt_register_t gdt_register;

// GDT Initialization functions.
void init_gdt()
{
	gdt_register.size = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_register.base_addr = (uint32_t)&gdt_entries;

	set_gdt_gate(0, 0, 0, 0, 0);
	set_gdt_gate(1, 0, 0xffffffff, 0x9a, 0xcf);
	set_gdt_gate(2, 0, 0xffffffff, 0x92, 0xcf);
	set_gdt_gate(3, 0, 0xffffffff, 0xfa, 0xcf);
	set_gdt_gate(4, 0, 0xffffffff, 0xf2, 0xcf);

	gdt_flush((uint32_t)&gdt_register);
}

// Helper of init_gdt.
void set_gdt_gate(int32_t index, uint32_t base, uint32_t size,
			 uint8_t flags, uint8_t granularity)
{
	gdt_entries[index].base_low = (base & 0xffff);
	gdt_entries[index].base_mid = ((base >> 16) & 0xff);
	gdt_entries[index].base_high = ((base >> 24) & 0xff);

	gdt_entries[index].size_low = (size & 0xffff);
	gdt_entries[index].access_flags = flags;

	gdt_entries[index].granularity = (size >> 16) & 0x0f;
	gdt_entries[index].granularity |= granularity & 0xf0;
}
