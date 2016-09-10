/* Hello World program */

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

main()
{
    int fd;
    ssize_t ret;
    char buf;
    fd = open("/proc/sys/net/ipv4/ip_forward", O_RDONLY);
    ret = read(fd, (void *) &buf, 1);
    printf("%c", buf);
    return 0;
}
