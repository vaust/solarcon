INC := ./inc
SRC := ./src

CFLAGS = -Wall -I$(INC) -D__REENTRANT__ -D__WAGO__
# CFLAGS = -D_REENTRANT -D__WAGO__

VPATH := $(SRC):$(INC)

OBJECTS := io_hl.o io_ll.o kbusapi.o main.o test.o block.o

all: testmich

testmich: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) -lpthread $(LDLIBS$(LDLIBS-$(@)))

clean:
	-rm -f testmich *.elf *.gdb *.o


io_hl.o: src/io_hl.c inc/gen_types.h inc/io_pab_types.h \
  inc/gen_types.h inc/io_wago_hwif.h \
  inc/io_pab_types.h inc/io_hl.h /usr/include/unistd.h
io_ll.o: src/io_ll.c inc/gen_types.h inc/io_wago_hwif.h \
  inc/io_pab_types.h inc/gen_types.h inc/io_pab_types.h inc/io_ll.h
kbusapi.o: src/kbusapi.c inc/kbusapi.h
main.o: src/main.c inc/gen_types.h inc/io_ll.h \
  inc/gen_types.h inc/io_hl.h inc/test.h
test.o: src/test.c inc/gen_types.h inc/io_ll.h \
 inc/gen_types.h inc/io_hl.h inc/test.h
block.o: src/block.c inc/block.h inc/gen_types.h
