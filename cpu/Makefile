CFLAGS := $(CFLAGS) -I../include/

all = cpu.o

OBJ = gdt_flush.o interrupt.o gdt.o isr.o dt.o timer.o

cpu.o: $(OBJ)
		@$(LD) -r $(OBJ) -o $@
		@echo LD cpu.o

%.o: %.c
		@${CC} -o $@ ${CFLAGS} -c $<
		@echo CC $<

%.o: %.asm
		@nasm -f elf $< -o $@
		@echo ASM $<
