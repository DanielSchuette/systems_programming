#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFSIZE 1024
int main(int argc, char *argv[])
{
    // get current process id
    pid_t pid = getpid();

    // print current process id
    printf("my pid: %d\n", pid);

    // wait for input from stdin
    fgetc(stdin);

    // return with status 0
    return 0;
}
