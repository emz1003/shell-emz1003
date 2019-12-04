all: main.o
	gcc -o program main.o
main.o: main.c shell.h
	gcc -c shell.c shell.h
shell.o: shell.c shell.h
	gcc -c shell.c shell.h
clean:
	rm program *.o
run:
	./program