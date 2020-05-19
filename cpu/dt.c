/** @file : dt.c
 *  @brief: This module initializes global and interrup descriptor tables.
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
#include "../libc/mem.h"
#include "dt.h"

/* GDT Initialization functions. */
/* gdt_flush is defined in assembly. */
extern void gdt_flush(uint32_t);
static void init_gdt(void);
static void set_gdt_gate(int32_t index, uint32_t base, uint32_t size,
			 uint8_t flags, uint8_t granularity);

/* IDT Initialization functions. */
/* idt_flush is defined in assembly. */
extern void idt_flush(uint32_t);
static void init_idt(void);
static void set_idt_gate(uint8_t index, uint32_t offset,
			 uint16_t selector, uint8_t flags);

// GDT Data Structures.
gdt_entry_t gdt_entries[5];
gdt_register_t gdt_register;

// IDT Data Structures.
idt_entry_t idt_entries[256];
idt_register_t idt_register;

void init_dt()
{
	init_gdt();
	init_idt();
}

// GDT Initialization functions.
static void init_gdt()
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
static void set_gdt_gate(int32_t index, uint32_t base, uint32_t size,
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

// IDT Initialization Functions.
static void set_idt_gate(uint8_t index, uint32_t offset,
			 uint16_t selector, uint8_t flags)
{
	idt_entries[index].lower_offset = offset & 0xffff;
	idt_entries[index].higher_offset = (offset >> 16) & 0xffff;

	idt_entries[index].selector = selector;
	idt_entries[index].zero = 0x00;
	// Uncomment the OR when entering user mode.
	// Since the OR sets the privilage level to 3.
	idt_entries[index].flags = flags /* | 0x60 */;
}

static void init_idt()
{
	idt_register.size = (sizeof(idt_entry_t) * 256) - 1;
	idt_register.base_addr = (uint32_t)&idt_entries;

	memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

	set_idt_gate(0, (uint32_t)isr0, 0x08, 0x8e);
	set_idt_gate(1, (uint32_t)isr1, 0x08, 0x8e);
	set_idt_gate(2, (uint32_t)isr2, 0x08, 0x8e);
	set_idt_gate(3, (uint32_t)isr3, 0x08, 0x8e);
	set_idt_gate(4, (uint32_t)isr4, 0x08, 0x8e);
	set_idt_gate(5, (uint32_t)isr5, 0x08, 0x8e);
	set_idt_gate(6, (uint32_t)isr6, 0x08, 0x8e);
	set_idt_gate(7, (uint32_t)isr7, 0x08, 0x8e);
	set_idt_gate(8, (uint32_t)isr8, 0x08, 0x8e);
	set_idt_gate(9, (uint32_t)isr9, 0x08, 0x8e);
	set_idt_gate(10, (uint32_t)isr10, 0x08, 0x8e);
	set_idt_gate(11, (uint32_t)isr11, 0x08, 0x8e);
	set_idt_gate(12, (uint32_t)isr12, 0x08, 0x8e);
	set_idt_gate(13, (uint32_t)isr13, 0x08, 0x8e);
	set_idt_gate(14, (uint32_t)isr14, 0x08, 0x8e);
	set_idt_gate(15, (uint32_t)isr15, 0x08, 0x8e);
	set_idt_gate(16, (uint32_t)isr16, 0x08, 0x8e);
	set_idt_gate(17, (uint32_t)isr17, 0x08, 0x8e);
	set_idt_gate(18, (uint32_t)isr18, 0x08, 0x8e);
	set_idt_gate(19, (uint32_t)isr19, 0x08, 0x8e);
	set_idt_gate(20, (uint32_t)isr20, 0x08, 0x8e);
	set_idt_gate(21, (uint32_t)isr21, 0x08, 0x8e);
	set_idt_gate(22, (uint32_t)isr22, 0x08, 0x8e);
	set_idt_gate(23, (uint32_t)isr23, 0x08, 0x8e);
	set_idt_gate(24, (uint32_t)isr24, 0x08, 0x8e);
	set_idt_gate(25, (uint32_t)isr25, 0x08, 0x8e);
	set_idt_gate(26, (uint32_t)isr26, 0x08, 0x8e);
	set_idt_gate(27, (uint32_t)isr27, 0x08, 0x8e);
	set_idt_gate(28, (uint32_t)isr28, 0x08, 0x8e);
	set_idt_gate(29, (uint32_t)isr29, 0x08, 0x8e);
	set_idt_gate(30, (uint32_t)isr30, 0x08, 0x8e);
	set_idt_gate(31, (uint32_t)isr31, 0x08, 0x8e);

	idt_flush((uint32_t)&idt_register);
}
