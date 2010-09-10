#TOOL := D:/Tools/MinGW/bin
INC := ./inc
SRC := ./src
#CC := $(TOOL)/gcc.exe
#CFLAGS := -I$(INC) -D__TEST__ -D__REENTRANT__ -Wall
CFLAGS := -I$(INC) -D__TEST__ -Wall
VPATH := $(SRC):$(INC)
#OBJECTS := cntrl.o task.o zeit.o param.o solar.o fb.o hk.o ww.o sup.o kes.o thread.o
OBJECTS := cntrl.o task.o zeit.o param.o solar.o fb.o hk.o ww.o sup.o kes.o

test : $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)
#	$(CC) -fprofile-arcs -ftest-coverage -o $@ $(OBJECTS)

cntrl.o: cntrl.c \
  gen_types.h param.h zeit.h task.h zeit.h \
  solar.h fb.h sup.h hk.h ww.h kes.h
fb.o: fb.c gen_types.h fb.h gen_types.h sup.h \
  sup.h param.h
hk.o: hk.c gen_types.h param.h hk.h sup.h \
  gen_types.h sup.h
kes.o: kes.c param.h kes.h gen_types.h
param.o: param.c \
  param.h
solar.o: solar.c solar.h gen_types.h param.h
sup.o: sup.c sup.h gen_types.h gen_types.h
task.o: task.c gen_types.h param.h zeit.h \
  gen_types.h task.h zeit.h
# telnet.o: telnet.c \
#  io.h gen_types.h \
ww.o: ww.c param.h ww.h sup.h gen_types.h
zeit.o: zeit.c \
  gen_types.h param.h zeit.h gen_types.h


clean :
	rm *.o; rm test


