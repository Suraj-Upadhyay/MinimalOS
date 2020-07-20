;/** @file : 32bit-gdt.asm
; *  @brief: This module defines a simple global descriptor table for our
; *  		 32 bit operating system.
; *
; *  Copyright (C) 2020  Suraj Upadhyay <usuraj35@gmail.com>
; *
; *  This program is free software: you can redistribute it and/or modify
; *  it under the terms of the GNU General Public License as published by
; *  the Free Software Foundation, either version 3 of the License, or
; *  (at your option) any later version.
; *
; *  This program is distributed in the hope that it will be useful,
; *  but WITHOUT ANY WARRANTY; without even the implied warranty of
; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; *  GNU General Public License for more details.
; *
; *  You should have received a copy of the GNU General Public License
; *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
; **/

gdt_start:
	dd 0x0 ; 4 byte
	dd 0x0 ; 4 byte

gdt_code: 
	dw 0xffff    ; segment length, bits 0-15
	dw 0x0       ; segment base, bits 0-15
	db 0x0       ; segment base, bits 16-23
	db 10011010b ; flags (8 bits)
	db 11001111b ; flags (4 bits) + segment length, bits 16-19
	db 0x0       ; segment base, bits 24-31

gdt_data:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start ; address (32 bit)

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start