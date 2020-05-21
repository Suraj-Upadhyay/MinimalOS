/** @file : isr_st.h
 *  @brief: This module provides data structures for Interrupt Descriptor Table.
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

#ifndef ISR_ST_H
#define ISR_ST_H

#include <stdint.h>

struct idt_entry_struct {
	uint16_t lower_offset;		// Lower 16 bits of handler function's offset.
	uint16_t selector;		// Kernel Segment Selector.
	uint8_t zero;			// Next 8 bits must be zero.
	uint8_t flags;
	uint16_t higher_offset;		// Higher 16 bits of handler function's offset.
}__attribute__((packed));

struct idt_register_struct {
	uint16_t size;			// Size of the interrupt table.
	uint32_t base_addr;		// Base address of the interrupt table.
}__attribute__((packed));

struct register_t {
	uint32_t ds;                  // Data segment selector
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
	uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
	uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
};

typedef struct idt_entry_struct idt_entry_t;
typedef struct idt_register_struct idt_register_t;
typedef struct register_t register_t;

#endif /* !defined(ISR_ST_H). */
