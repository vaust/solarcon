
objects = main.o task.o zeit.o init_var.o log.o kbusapi.o \
          solar.o fb.o hk.o ww.o speicher1.o speicher2.o kessel.o

test: $(objects)
	gcc -o $@ $(objects)

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
speicher1.o: io.h vorgabe.h variablen.h zeitprogramm.h
speicher2.o: io.h vorgabe.h variablen.h zeitprogramm.h
kessel.o: io.h vorgabe.h variablen.h zeitprogramm.h

