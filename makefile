all: shell.o
	gcc -o program shell.o
shell.o: shell.c shellfunc.h
	gcc -c shell.c shellfunc.h
clean: