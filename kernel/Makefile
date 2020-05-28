all : kernel.o

CFLAGS := $(CFLAGS) -I../include/

%.o: %.c
		@$(CC) -o $@ $(CFLAGS) -c $<
		@echo CC $<
