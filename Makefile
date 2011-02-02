INC := ./inc
SRC := ./src

CFLAGS = -Wall -I$(INC) -D__REENTRANT__ -D__WAGO__
# CFLAGS = -D_REENTRANT -D__WAGO__

VPATH := $(SRC):$(INC)

OBJECTS := cntrl.o task.o zeit.o param.o sol.o fb.o hk.o ww.o sup.o kes.o io.o io_v2.o telnet.o server.o \
 kbusapi.o err.o

all: rca7

rca7: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) -lpthread $(LDLIBS$(LDLIBS-$(@)))

romfs:
	$(ROMFSINST) /bin/rca6
	chmod 755 $(ROMFSDIR)/bin/rca6

clean:
	-rm -f rca7 *.elf *.gdb *.o


cntrl.o: cntrl.c \
  io.h gen_types.h \
  gen_types.h param.h zeit.h task.h param.h zeit.h sol.h \
  fb.h sup.h hk.h ww.h kes.h io_v2.h err.h cntrl.h \
  task.h sol.h fb.h hk.h ww.h kes.h err.h
err.o: err.c gen_types.h param.h err.h gen_types.h
fb.o: fb.c gen_types.h fb.h gen_types.h sup.h sup.h \
  param.h
hk.o: hk.c gen_types.h param.h hk.h sup.h gen_types.h \
  sup.h
io.o: io.c gen_types.h io_wago_hwif.h io_pab_types.h \
  gen_types.h io_pab_types.h io.h
io_v2.o: io_v2.c gen_types.h io_pab_types.h gen_types.h \
  io_wago_hwif.h io_pab_types.h io_v2.h
kes.o: kes.c gen_types.h param.h kes.h gen_types.h
param.o: param.c \
  param.h
sol.o: sol.c sol.h gen_types.h param.h
sup.o: sup.c gen_types.h param.h sup.h gen_types.h
task.o: task.c gen_types.h param.h zeit.h gen_types.h \
  task.h param.h zeit.h
telnet.o: telnet.c \
  io.h gen_types.h \
  gen_types.h param.h cntrl.h sup.h zeit.h task.h param.h \
  sol.h fb.h hk.h ww.h kes.h err.h zeit.h task.h \
  version.h server.h telnet_vars.h
ww.o: ww.c param.h ww.h sup.h gen_types.h
zeit.o: zeit.c \
  gen_types.h param.h zeit.h gen_types.h
