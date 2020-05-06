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
