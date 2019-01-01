/*
 * A simple shell-like program that
 * reads from stdin and executes
 * commands.
 */
#include "apue.h"
#include <sys/wait.h>

int main(void)
{
    char    buf[MAXLINE];
    pid_t   pid;
    int     status;

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
    exit(0);
}
