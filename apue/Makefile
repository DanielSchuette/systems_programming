# modify Makefile to build progs from
# source that require error.c or log.c
prog: get_limits.o
	gcc get_limits.o error.o -o prog

get_limits.o: error.o
	gcc get_limits.c -c -o get_limits.o

error.o:
	gcc error.c -c -o error.o

clean:
	rm *.o
	rm prog
