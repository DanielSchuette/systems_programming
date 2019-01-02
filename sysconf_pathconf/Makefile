conf: conf.o
	gcc conf.o error.o -o conf

conf.o: error.o
	gcc conf.c -c -o conf.o

error.o:
	gcc error.c -c -o error.o

clean:
	rm *.o
	rm conf
