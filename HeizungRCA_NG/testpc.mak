TOOL = D:/Tools/MinGW/bin
INC = ./inc
SRC = ./src
CC = $(TOOL)/gcc.exe
CFLAGS = -I$(INC) -D__TEST__ -Wall
VPATH = src:inc
objects = cntrl.o task.o zeit.o param.o solar.o fb.o hk.o ww.o sup.o kes.o 

test : $(objects)
	$(CC) -o $@ $(objects)

