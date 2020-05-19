/** @file : dt.h
 *  @brief: This module declares global and interrupt descriptor tables'
 *          initialization funcitons.
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

#ifndef DT_H
#define DT_H

#include <stdint.h>

struct gdt_entry_struct {
	uint16_t size_low;		// Lower 16 bits of size limit.
	uint16_t base_low;	 	// Lower 16 bits of base address.
	uint8_t base_mid;		// Next 8 bits of base address.
	uint8_t access_flags;		// 8 bits of Access flags.
					// Type : 5, DT : 1, DPL : 1, P : 1.
	uint8_t granularity;
	uint8_t base_high;		// Next 8 bits of base address.
}__attribute__((packed));

struct idt_entry_struct {
	uint16_t lower_offset;		// Lower 16 bits of handler function's offset.
	uint16_t selector;		// Kernel Segment Selector.
	uint8_t zero;			// Next 8 bits must be zero.
	uint8_t flags;
	uint16_t higher_offset;		// Higher 16 bits of handler function's offset.
}__attribute__((packed));

struct gdt_register_struct {
	uint16_t size;			// Size of the descriptor table.
	uint32_t base_addr;		// Base address of the descriptor table.
}__attribute__((packed));

struct idt_register_struct {
	uint16_t size;			// Size of the interrupt table.
	uint32_t base_addr;		// Base address of the interrupt table.
}__attribute__((packed));

// Type define all the names to sensible and shorter alternatives.
typedef struct gdt_entry_struct gdt_entry_t;
typedef struct gdt_register_struct gdt_register_t;

typedef struct idt_entry_struct idt_entry_t;
typedef struct idt_register_struct idt_register_t;

/* init_dt : Initializes and loads the Global Descriptor Table and
 * Interrupt Descriptor Table. */
void init_dt(void);

/* Declare ISR handlers. */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif /* !defined(DT_H). */
