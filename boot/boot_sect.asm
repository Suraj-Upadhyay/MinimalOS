;/** @file : boot_sect.asm
; *  @brief: This module boots our operating system, loads the kernel into
; *          memory, performs the switch to 32 bit protecetd mode
; *  		 and calls the kernel code.
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

[org 0x7c00]
KERNELOFFSET equ 0x1000
    mov [BOOT_DRIVE], dl

    mov bp, 0x9000
    mov sp, bp

    mov bx, KERNELOFFSET
    mov dh, 15
    mov dl, [BOOT_DRIVE]
    call disk_load

    call switch_to_pm

    jmp $

%include "print.asm"
%include "32bit-switch.asm"
%include "32bit-gdt.asm"
%include "read_disk.asm"

[bits 32]
BEGIN_PM:
    call KERNELOFFSET

jmp $

BOOT_DRIVE: db 0

times 510 - ($ - $$) db 0
dw 0xaa55
