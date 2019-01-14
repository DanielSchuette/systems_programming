# modify Makefile to build progs from
# source that require error.c or log.c
PROG.c = hole.c
PROG.o = hole.o

prog: $(PROG.o)
	gcc $(PROG.o) error.o -o prog

$(PROG.o): error.o
	gcc $(PROG.c) -c -o $(PROG.o)

error.o:
	gcc error.c -c -o error.o

clean:
	rm *.o
	rm prog
