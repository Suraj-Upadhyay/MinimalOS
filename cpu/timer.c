/** @file : timer.c
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
#include "../drivers/screen.h"
#include "../drivers/ports.h"
#include "../cpu/isr_st.h"
#include "../cpu/isr.h"
#include "timer.h"

uint32_t tick = 0;

static void timer_callback(register_t reg)
{
    tick++;
    print("Tick: ");
    print_dec(tick);
    print("\n");
}

void init_timer(uint32_t frequency)
{
    register_interrupt_handler(32, timer_callback);
    uint32_t divisor = 1193180 / frequency;
    uint8_t low = (uint8_t)(divisor & 0xff);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xff);
    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}
