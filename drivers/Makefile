CFLAGS := $(CFLAGS) -I../include/

all : drivers.o

OBJ = keyboard.o ports.o screen.o

drivers.o: $(OBJ)
		@$(LD) -r $(OBJ) -o $@
		@echo LD drivers.o

%.o: %.c
		@${CC} -o $@ ${CFLAGS} -c $<
		@echo CC $<
