print_hex:
    pusha
    mov cx, 0x00
print_hex_loop:
    cmp cx, 0x04
    je print_hex_print_data
    mov ax, dx
    and ax, 0x000f
    cmp ax, 0x0a
    jl print_hex_convert_to_numeral
print_hex_convert_to_alpha:
        add ax, 0x57
        jmp print_hex_copy_data
print_hex_convert_to_numeral:
        add ax, 0x30
print_hex_copy_data:
        mov bx, HEX_MSG
        add bx, 0x05
        sub bx, cx
        mov [bx], al
    shr dx, 4
    add cx, 0x01
    jmp print_hex_loop
print_hex_print_data:
    mov dx, HEX_MSG
    call print_string
print_hex_exit:
    popa
    ret

HEX_MSG: db "0x0000", 0

print_string:
    pusha
    mov bx, dx
    mov ah, 0x0e
print_string_loop:
    mov al, [bx]
    cmp al, 0x00
    je print_string_exit
    int 0x10
    add bx, 0x01
    jmp print_string_loop
print_string_exit:
    popa
    ret

[bits 32]
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY
print_string_pm_loop:
    mov al, [ebx]
    cmp al, 0
    je print_strint_pm_exit
    mov ah, WHITE_ON_BLACK
    mov [edx], ax
    add edx, 0x02
    add ebx, 0x01
    jmp print_string_pm_loop
print_strint_pm_exit:
    popa
    ret