/*
 * signal.c demonstrates how a process receives a signal and handles it using a callback function
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void signal_callback_handler (int signum)
{
    printf("caught signal: [%d]\n", signum);
    //exit(1); /* comment out to disable ctrl + c */
}

int main(int argc, char *argv[])
{
    signal(SIGINT, signal_callback_handler);
    while (1) {}
    return 0;
}
