TOOL := D:/Tools/MinGW/bin
INC := ./inc
SRC := ./src
CC := $(TOOL)/gcc.exe
CFLAGS := -I$(INC) -D__TEST__ -D__WIN__ -Wall
#CFLAGS := -I$(INC) -D__TEST__ -D__WIN__ -D__REENTRANT__ -Wall
#CFLAGS := -I$(INC) -D__WIN__ -Wall
VPATH := src:inc
#OBJECTS := cntrl.o task.o zeit.o param.o solar.o fb.o hk.o ww.o sup.o kes.o thread.o
OBJECTS := cntrl.o task.o zeit.o param.o solar.o fb.o hk.o ww.o sup.o kes.o

test : $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

cntrl.o: src\cntrl.c \
  gen_types.h param.h zeit.h task.h zeit.h \
  solar.h fb.h sup.h hk.h ww.h kes.h
fb.o: src\fb.c gen_types.h fb.h gen_types.h sup.h \
  sup.h param.h
hk.o: src\hk.c gen_types.h param.h hk.h sup.h \
  gen_types.h sup.h
kes.o: src\kes.c param.h kes.h gen_types.h
param.o: src\param.c \
  param.h
solar.o: src\solar.c solar.h gen_types.h param.h
sup.o: src\sup.c sup.h gen_types.h gen_types.h
task.o: src\task.c gen_types.h param.h zeit.h \
  gen_types.h task.h zeit.h
# telnet.o: src\telnet.c \
#  io.h gen_types.h \
ww.o: src\ww.c param.h ww.h sup.h gen_types.h
zeit.o: src\zeit.c \
  gen_types.h param.h zeit.h gen_types.h
