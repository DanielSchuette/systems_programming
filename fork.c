/*
 * fork(), wait(), exec(), and signal() comprise the main machinery via which processed are started 
 * and communicate in a UNIX system; all systems running under a Unix OS are created this way from 
 * one common parent with multiple (thousends) of children 
 *
 * a shell is a 'job control system' that
 * can create and communicate between processes with relatively low level access to OS capabilities.
 *
 * see also: signal.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFSIZE 1024
int main(int argc, char *argv[])
{
    char buf[BUFSIZE];
    size_t readlen, writelen, slen;
    int loop_count = 20;
    int status = 0;
    pid_t cpid, mypid; /* child and parent process ids */
    pid_t pid = getpid();
    printf("parent pid: %d\n", pid);
    cpid = fork(); /* returns the process id of the spawned child process or an integer <= 0 */
    if (cpid > 0) { /* child process */
        mypid = getpid();
        printf("[%d] parent of [%d]\n", mypid, cpid);
        for (int i = 0; i < 5; i++) {
            printf("parent doing some stuff\n");
        }
        printf("parent going to sleep...\n");
        pid_t epid = wait(&status); /* wants a pointer to an int and returns the pid of the process it waited for */
        printf("parent woke up from [%d]\n", epid);
        printf("parent running a loop\n");
        for (int i = 0; i < loop_count; i++) {
            printf("parent i: %d\n", i);
        }
    } else if ( cpid == 0) { /* parent process */
        mypid = getpid();
        printf("[%d] child\n", mypid);
        printf("child is running a loop\n");
        for (int i = 0; i < loop_count; i++) {
            printf("child i: %d\n", i);
        }
    } else {
        perror("fork failed");
        exit(1);
    }
    return 0;
}
