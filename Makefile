C_SOURCES = $(wildcard kernel/*.c drivers/*.c libc/*.c cpu/*.c)
HEADERS = $(wildcard include/*/*.h)

OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o cpu/gdt_flush.o}

CC = i386-elf-gcc
LD = i386-elf-ld

CFLAGS = -g -ffreestanding -Wall -Wextra -m32 -Iinclude

os-image.bin: boot/boot_sect.bin kernel.bin
		@cat $^ > os-image.bin
		@echo Built Successfully

kernel.bin: boot/kernel_entry.o ${OBJ}
		@${LD} -o $@ -Ttext 0x1000 $^ --oformat binary
		@echo LD $<

%.o: %.c ${HEADERS}
		@${CC} -o $@ ${CFLAGS} -c $<
		@echo CC $<

%.o: %.asm
		@nasm -f elf $< -o $@
		@echo ASM $<

%.bin: %.asm
		@nasm -f bin -I boot/ $< -o $@
		@echo ASM $<

run: os-image.bin
		qemu-system-i386 -fda os-image.bin

clean:
		rm -rf *.bin *.dis *.o os-image.bin
		rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o libc/*.o cpu/*.o
