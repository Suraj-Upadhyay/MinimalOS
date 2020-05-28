all : buildsubdirs os-image.bin

CC = i386-elf-gcc
LD = i386-elf-ld

CFLAGS = -g -ffreestanding -Wall -Wextra -m32

ARCHIVES = kernel/kernel.o cpu/cpu.o libc/libc.o
DRIVERS = drivers/drivers.o

SUBDIRS = boot kernel cpu drivers libc

export

os-image.bin: boot/boot_sect.bin kernel.bin
		@cat $^ > os-image.bin
		@echo Built Successfully

kernel.bin: boot/kernel_entry.o ${ARCHIVES} ${DRIVERS}
		@${LD} -o $@ -Ttext 0x1000 $^ --oformat binary
		@echo LD $<

.PHONY: buildsubdirs $(SUBDIRS)

buildsubdirs: $(SUBDIRS)

$(SUBDIRS):
		@$(MAKE) --no-print-directory -C $@

run: buildsubdirs os-image.bin
		@qemu-system-i386 -fda os-image.bin

clean:
		@rm -rf *.bin *.dis *.o os-image.bin
		@rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o libc/*.o cpu/*.o
