;/** @file : read_disk.asm
; *  @brief: This module provides functions for reading disk using BIOS
; *  		 in 16 bit real mode.
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

disk_load:
	pusha
	push dx
	mov ah, 0x02
	mov al, dh
	mov ch, 0x00
	mov cl, 0x02
	mov dh, 0x00
	int 0x13
	jc disk_error
	pop dx
	cmp al, dh
	jne disk_sector_error
	popa
	ret
disk_error:
	mov dx, DISK_ERROR_MSG
	call print_string
	jmp $
disk_sector_error:
	mov dx, DISK_SECTOR_ERROR_MSG
	call print_string
	jmp $

DISK_ERROR_MSG: db "Disk read error", 0
DISK_SECTOR_ERROR_MSG: db "Incorrect sectors read", 0