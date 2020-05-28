/** @file : isr.c
 *  @brief: This module defines functions which initialize the Interrupt
 * 			Descriptor Table and functions which handle ISR and IRQ Requests.
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
#include "minimalos/drivers/screen.h"
#include "minimalos/drivers/ports.h"
#include "minimalos/libc/mem.h"
#include "minimalos/cpu/isr_st.h"
#include "minimalos/cpu/isr.h"

// IDT Data Structures.
idt_entry_t idt_entries[256];
idt_register_t idt_register;

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler)
{
	interrupt_handlers[n] = handler;
}

// ISR request handler.
void isr_handler(register_t reg)
{
	print("Received interrupt : ");
	print_hex(reg.int_no);
	print("\n");
}

// IRQ request handler.
void irq_handler(register_t reg)
{
	/* Send an EOI (end of interrupt) signal to the PICs. */
	// If this interrupt involved the slave PIC.
	if (reg.int_no >= 40) {
		port_byte_out(0xa0, 0x20);
	}

	port_byte_out(0x20, 0x20);

	if (interrupt_handlers[reg.int_no] != 0) {
		isr_t handler = interrupt_handlers[reg.int_no];
		handler(reg);
	}
}

// IDT Initialization Functions.
void init_idt()
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

	/* Remap PIC. */
	port_byte_out(0x20, 0x11);
	port_byte_out(0xa0, 0x11);
	port_byte_out(0x21, 0x20);
	port_byte_out(0xa1, 0x28);
	port_byte_out(0x21, 0x04);
	port_byte_out(0xa1, 0x02);
	port_byte_out(0x21, 0x01);
	port_byte_out(0xa1, 0x01);
	port_byte_out(0x21, 0x00);
	port_byte_out(0xa1, 0x00);

	set_idt_gate(IRQ0, (uint32_t)irq0, 0x08, 0x8e);
	set_idt_gate(IRQ1, (uint32_t)irq1, 0x08, 0x8e);
	set_idt_gate(IRQ2, (uint32_t)irq2, 0x08, 0x8e);
	set_idt_gate(IRQ3, (uint32_t)irq3, 0x08, 0x8e);
	set_idt_gate(IRQ4, (uint32_t)irq4, 0x08, 0x8e);
	set_idt_gate(IRQ5, (uint32_t)irq5, 0x08, 0x8e);
	set_idt_gate(IRQ6, (uint32_t)irq6, 0x08, 0x8e);
	set_idt_gate(IRQ7, (uint32_t)irq7, 0x08, 0x8e);
	set_idt_gate(IRQ8, (uint32_t)irq8, 0x08, 0x8e);
	set_idt_gate(IRQ9, (uint32_t)irq9, 0x08, 0x8e);
	set_idt_gate(IRQ10, (uint32_t)irq10, 0x08, 0x8e);
	set_idt_gate(IRQ11, (uint32_t)irq11, 0x08, 0x8e);
	set_idt_gate(IRQ12, (uint32_t)irq12, 0x08, 0x8e);
	set_idt_gate(IRQ13, (uint32_t)irq13, 0x08, 0x8e);
	set_idt_gate(IRQ14, (uint32_t)irq14, 0x08, 0x8e);
	set_idt_gate(IRQ15, (uint32_t)irq15, 0x08, 0x8e);

	idt_flush((uint32_t)&idt_register);
}

void set_idt_gate(uint8_t index, uint32_t offset,
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
