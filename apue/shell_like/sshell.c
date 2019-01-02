/*
 * A simple shell-like program that reads 
 * from stdin and executes commands.
 * It depends on the APUE header and its
 * error handling routines in `error.c'.
 * Interrupt signals are caught and 
 * handled appropriately.
 */
#include "apue.h"
#include <sys/wait.h>

static void sig_int(int); /* signal-catching callback */

int main(void)
{
    char    buf[MAXLINE];
    pid_t   pid;
    int     status;

    if (signal(SIGINT, sig_int) == SIG_ERR) /* use SIG_IGN to ignore SIGINTs */
        err_sys("signal error");

    printf("%% "); /* print a command prompt */
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf)-1] == '\n')
            buf[strlen(buf)-1] = 0; /* replace new line with null */
        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) { /* child */
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        /* parent */
        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }
    return 0;
}

void sig_int(int signum)
{
    printf("interrupt %d\n%% ", signum);
}
