[org 0x7c00]
KERNELOFFSET equ 0x1000
    mov [BOOT_DRIVE], dl

    mov bp, 0x9000
    mov sp, bp

    mov dx, MSGRM
    call print_string

    mov dx, MSG_LOAD_KERNEL
    call print_string

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
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    call KERNELOFFSET

jmp $

BOOT_DRIVE: db 0
MSGRM:      db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE:  db "Successfully landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL: db "Loading kernel into memory", 0

times 510 - ($ - $$) db 0
dw 0xaa55
