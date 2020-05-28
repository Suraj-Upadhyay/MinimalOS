CFLAGS := $(CFLAGS) -I../include/

all : libc.o

OBJ = mem.o

libc.o: $(OBJ)
		@$(LD) -r $(OBJ) -o $@
		@echo LD libc.o

%.o: %.c
		@${CC} -o $@ ${CFLAGS} -c $<
		@echo CC $<
