all: rca

rca: control.o init_var.o kbusapi.o
	$(CC) $(LDFLAGS) -o $@ control.o init_var.o kbusapi.o $(LDLIBS$(LDLIBS-$(@)))
	cp rca /targetfs/

romfs:
	$(ROMFSINST) /bin/rca
	chmod 755 $(ROMFSDIR)/bin/rca

clean:
	-rm -f rca *.elf *.gdb *.o

init_var.o: init_var.c io.h variablen.h vorgabe.h 
control.o: control.c kbusapi.h variablen.h vorgabe.h io.h 
kbusapi.o: kbusapi.h

