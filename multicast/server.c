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
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    char buf[64];
    socklen_t l = sizeof(addr);
    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        printf("failed to join multicast group\n");
        close(sock);
        return -1;
    }
    while (1) {
        int n = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &l);
        if (n > 0) {
            printf("RECIVE from %s => buf: %s\n", inet_ntoa(addr.sin_addr), buf);
        }
    }

    setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
    close(sock);
    return 0;
}
