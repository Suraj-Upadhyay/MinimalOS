C_SOURCES = $(wildcard kernel/*.c drivers/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h libc/*.h)

OBJ = ${C_SOURCES:.c=.o}

os-image.bin: boot/boot_sect.bin kernel.bin
		cat $^ > os-image.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
		i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
		i386-elf-gcc -o $@ -ffreestanding -c $<

%.o: %.asm
		nasm -f elf $< -o $@

%.bin: %.asm
		nasm -f bin -I boot/ $< -o $@

run: os-image.bin
		qemu-system-i386 -fda os-image.bin

clean:
		rm -rf *.bin *.dis *.o os-image.bin
		rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o