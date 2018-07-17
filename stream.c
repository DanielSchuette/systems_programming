/*
 * stream.c demonstrate the basic functionality of the C file streaming API
 * do not mix fopen and open files; whereas streams have a 'handle' on a file,
 * low level open operations return a file descriptor (thus, not an API/library, but SYSCALL)
 * file descriptors are nothing else but INTs whereas FILE * are pointers to structures
 * see syscall_open.c for an example
 */
#include <stdio.h>
#include <string.h>

#define BUFLEN 256
FILE *outfile;
char mybuf[BUFLEN];

int storetofile(void) 
{
    outfile = fopen("/Users/daniel/Desktop/tmp.txt", "w+");
    if (!outfile) {
        return (-1);
    }
    while (1) {
        char *instring;
        instring = fgets(mybuf, BUFLEN, stdin); /* catches overflow */

        // check for error or EOF (^D)
        if (!instring || strlen(instring) == 0) {
            break;
        }
        // write string to output file, exit on error
        if (fputs(instring, outfile) < 0) {
            break;
        }
    }
    fclose(outfile); // flushes from userspace
    return 0;
}

int main(void)
{
    storetofile();
    return 0;
}
