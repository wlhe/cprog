#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <net/if.h>
#include <net/route.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

static int add_route(const char *dst, const char *gw, const char *mask)
{
    int sock_fd;

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        printf("failed to create udp socket\n");
        return -1;
    }
    // add route
    struct rtentry route;
    struct sockaddr_in *paddr;
    memset(&route, 0, sizeof(route));
    paddr = (struct sockaddr_in *)&route.rt_gateway;
    paddr->sin_family = AF_INET;
    paddr->sin_addr.s_addr = inet_addr(gw);
    paddr = (struct sockaddr_in *)&route.rt_dst;
    paddr->sin_family = AF_INET;
    paddr->sin_addr.s_addr = inet_addr(dst);
    paddr = (struct sockaddr_in *)&route.rt_genmask;
    paddr->sin_family = AF_INET;
    paddr->sin_addr.s_addr = inet_addr(mask);
    route.rt_flags = RTF_UP | RTF_GATEWAY;
    route.rt_metric = 0;
    int err = ioctl(sock_fd, SIOCADDRT, &route);
    if (err < 0 && errno != EEXIST) {
        printf("failed to add gateway, error %d, %s\n", errno, strerror(errno));
        // close(sock_fd);
        // return -1;
    }
    // sleep(1);
    close(sock_fd);
    return err;
}

int main()
{
    add_route("0.0.0.0", "192.168.1.1", "0.0.0.0");

    return 0;
}