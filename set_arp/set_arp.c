#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <net/if_arp.h>

main (int argc, char *argv[]) {
    int ret, fd;
    struct arpreq arpreq;
    struct sockaddr_in *sin;

    bzero(&arpreq, sizeof(struct arpreq));
    sin = (struct sockaddr_in *)&arpreq.arp_pa;

    sin->sin_addr.s_addr = inet_addr("1.1.1.1");

    sscanf("aa:aa:aa:aa:aa:aa", "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
        &arpreq.arp_ha.sa_data[0], &arpreq.arp_ha.sa_data[1], &arpreq.arp_ha.sa_data[2],
        &arpreq.arp_ha.sa_data[3], &arpreq.arp_ha.sa_data[4], &arpreq.arp_ha.sa_data[5]);
    
    arpreq.arp_pa.sa_family = AF_INET;
    arpreq.arp_ha.sa_family = AF_UNIX;

    arpreq.arp_flags = ATF_PERM;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ret = ioctl(fd, SIOCSARP, (caddr_t)&arpreq);

    close(fd);

    if(ret != 0){
        perror("ioctl");
    }
}
