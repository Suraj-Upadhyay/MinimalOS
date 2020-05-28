all : boot_sect.bin kernel_entry.o

%.o: %.asm
		@nasm -f elf $< -o $@
		@echo ASM $<

%.bin: %.asm
		@nasm -f bin -I boot/ $< -o $@
		@echo ASM $<
