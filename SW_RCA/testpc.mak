test: init_var.o control.o
	gcc -o $@ init_var.o control.o

init_var.o: init_var.c
	gcc -c init_var.c
    
control.o: control.c
	gcc control.c

