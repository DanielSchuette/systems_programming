/*
 * This example demonstrates how to get
 * platform-dependent compile-time or 
 * runtime limits, in this case the max
 * length of a path name. First, symbolic
 * constants in <limits.h> are checked,
 * then `pathconfig' is used. Lastly, if
 * PATH_MAX is undeterminate, a value is
 * guessed by repeatedly reallocating
 * storage until a system call like `getpwd'
 * succeeds (not done in this example; here,
 * 1024 is used to make things easier).
 */
#include "apue.h"
#include <errno.h>
#include <limits.h>

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

/* 
 * If PATH_MAX is undeterminate, this is mostly
 * likely not accurate at all.
 */
#define PATH_MAX_GUESS 1024

/*
 * path_alloc: allocate memory for path name and
 * return size via `sizep'.
 */
char *path_alloc(size_t *sizep)
{
    char    *ptr;
    size_t  size;

    if (posix_version == 0)
        posix_version = sysconf(_SC_VERSION);
    if (xsi_version == 0)
        xsi_version = sysconf(_SC_XOPEN_VERSION);

    if (pathmax == 0) {
        errno = 0;
        if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
            if (errno == 0) /* no error, so its indeterminate */
                pathmax = PATH_MAX_GUESS; 
            else
                err_sys("pathconf error for PC_PATH_MAX");
        } else { /* at this point, we got a value from pathconf */
            pathmax++; /* relative to root, so add one */
        }
    }
    /*
     * Before POSIX.1-2001, we aren't guaranteed that PATH_MAX
     * includes the terminating null byte. Same goes for XPG3.
     */
    if ((posix_version < 200112L) && (xsi_version < 4))
        size = pathmax + 1;
    else
        size = pathmax;

    if ((ptr = (char *)malloc(size * sizeof(char))) == NULL)
        err_sys("malloc error for pathname");

    if (sizep != NULL)
        *sizep = size;
    return ptr;
}
