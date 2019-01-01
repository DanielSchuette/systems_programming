/*
 * Get user and group IDs.
 */
#include "apue.h"

int main(void)
{
    printf("user %d, group %d\n", getuid(), getgid());
    return 0;
}
