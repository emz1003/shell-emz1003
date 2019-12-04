all: main.o
	gcc -o program main.o
main.o: main.c shell.h
	gcc -c shell.c shell.h
shell.o: shell.c shellfunc.h
	gcc -c shell.c shellfunc.h
clean:
