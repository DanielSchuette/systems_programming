# Modify Makefile to build progs from
# source that require error.c or log.c.
# As an alternative to setting PROGNAME
# in this script, use:
# $make PROGNAME=<program_name>
PROGNAME := get_limits
PROG.c := $(PROGNAME).c
PROG.o := $(PROG.c:.c=.o)

prog: $(PROG.o)
	gcc $(PROG.o) error.o -o prog

$(PROG.o): error.o
	gcc $(PROG.c) -c -o $(PROG.o)

error.o:
	gcc error.c -c -o error.o

clean:
	rm *.o
	rm prog
