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

