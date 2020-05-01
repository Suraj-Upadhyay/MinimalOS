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