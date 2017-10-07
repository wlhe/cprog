#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MULT_ADDR "224.0.0.250"
#define MULT_PORT 9999

int main()
{
    struct sockaddr_in addr;
    int sock;
    struct ip_mreq mreq;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        printf("failed to create udp socket\n");
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(MULT_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr))) {
        printf("failed to bind socket\n");
        close(sock);
        return -1;
    }

    memset(&mreq, 0, sizeof(mreq));
    mreq.imr_multiaddr.s_addr = inet_addr(MULT_ADDR);

    struct ifreq ifr[10];
    struct ifconf ifc;
    ifc.ifc_req = ifr;
    ifc.ifc_len = sizeof(ifr);

    if (ioctl(sock, SIOCGIFCONF, &ifc) < 0) {
        printf("ioctl SIOCGIFCONF error\n");
        return -1;
    }
    struct sockaddr_in *paddr = NULL;
    int m = (ifc.ifc_len / sizeof(struct ifreq));
    int i = 0;

    char buf[64];
    socklen_t l = sizeof(addr);

    for (i = 0; i < m; i++) {
        // need add all interface to multicast group
        paddr = (struct sockaddr_in *)&(ifr[i].ifr_addr);
        if (strcmp("127.0.0.1", inet_ntoa(paddr->sin_addr)) == 0) {
            continue;
        }

        mreq.imr_interface.s_addr = paddr->sin_addr.s_addr;
        if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
            printf("failed to join multicast group\n");
            close(sock);
            return -1;
        }
    }
    while (1) {
        int n = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &l);
        if (n > 0) {
            printf("RECIVE from %s => buf: %s\n", inet_ntoa(addr.sin_addr), buf);
        }
        printf("---------------------\n");
    }
    for (i = 0; i < m; i++) {
        if (strcmp("127.0.0.1", inet_ntoa(paddr->sin_addr)) == 0) {
            continue;
        }
        setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
    }

    close(sock);
    return 0;
}
