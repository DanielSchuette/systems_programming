sshell: sshell.o
	gcc error.o sshell.o -o sshell

sshell.o: error.o
	gcc sshell.c -c -o sshell.o

error.o:
	gcc error.c -c -o error.o

clean:
	rm *.o
	rm sshell
