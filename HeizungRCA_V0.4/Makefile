CFLAGS = -D_REENTRANT -D__WAGO__ -D__DEBUG__
# CFLAGS = -D_REENTRANT -D__WAGO__

objects = server.o main.o task.o zeit.o init_var.o log.o kbusapi.o \
          solar.o fb.o hk.o ww.o speicher.o kessel.o

all: rca4_z

rca4_z: $(objects)
	$(CC) $(LDFLAGS) -o $@ $(objects) -lpthread $(LDLIBS$(LDLIBS-$(@)))
#	cp rca2 /targetfs/

romfs:
	$(ROMFSINST) /bin/rca4_z
	chmod 755 $(ROMFSDIR)/bin/rca4_z

clean:
	-rm -f rca4_z *.elf *.gdb *.o

server.o: server.h io.h vorgabe.h variablen.h
main.o: io.h vorgabe.h variablen.h
task.o: io.h vorgabe.h variablen.h zeitprogramm.h
zeit.o: vorgabe.h variablen.h zeitprogramm.h
init_var.o: vorgabe.h variablen.h zeitprogramm.h
log.o: io.h vorgabe.h variablen.h zeitprogramm.h
kbusapi.o: kbusapi.h
solar.o: io.h vorgabe.h variablen.h zeitprogramm.h
fb.o: io.h vorgabe.h variablen.h zeitprogramm.h
hk.o: io.h vorgabe.h variablen.h zeitprogramm.h
ww.o: io.h vorgabe.h variablen.h zeitprogramm.h
speicher.o: io.h vorgabe.h variablen.h zeitprogramm.h
kessel.o: io.h vorgabe.h variablen.h zeitprogramm.h
