/*
 * this program DOES NOT COMPILE! 
 * the following struct is just an example of how a
 * file operations struct might look like that permits
 * low level abstract to implement all kinds of different
 * file systems within the same kernel; it exemplifies
 * many of the basic operations that one might want to 
 * perform on a file like read, write, open, close, ...
 */
struct file_operations {
    struct module *owner;
    loff_t  (*llseek) (struct file *, loff_t, int);
    ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
    ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
    ssize_t (*aio_read) ...;
    ssize_t (*aio_write) ...;
    int (*readdir) ...;
    unsigned int (*poll) ...;
    int (*ioctl) ...;
    int (*mmap) ...;
    int (*open) ...;
    int (*flush) ...;
    int (*release) ...;
    int (*fsync) ...;
    int (*fasync) ...;
    int (*flock) ...;
    [...]
}
