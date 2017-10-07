#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MULT_ADDR "224.0.0.250"
#define MULT_PORT 9999
#define MSG "multicast message"
int main()
{

    int sock;
    struct sockaddr_in mult_addr;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        return -1;
    }

    memset(&mult_addr, 0, sizeof(mult_addr));
    mult_addr.sin_family = AF_INET;
    mult_addr.sin_port = htons(MULT_PORT);
    mult_addr.sin_addr.s_addr = inet_addr(MULT_ADDR);

    socklen_t l = sizeof(mult_addr);

    unsigned char ttl = 20;
    l = sizeof(ttl);
    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&ttl, l);
    l = sizeof(mult_addr);

    struct ifreq ifr[10];
    struct ifconf ifc;
    ifc.ifc_req = ifr;
    ifc.ifc_len = sizeof(ifr);

    if (ioctl(sock, SIOCGIFCONF, &ifc) < 0) {
        printf("ioctl SIOCGIFCONF error\n");
        return -1;
    }
    struct sockaddr_in *addr = NULL;
    int n = (ifc.ifc_len / sizeof(struct ifreq));
    int i = 0;

    // forbid loop, not send to ownself
    // common this for local machine test
    unsigned char loop = 0;
    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));

    while (1) {
        for (i = 0; i < n; i++) {
            addr = (struct sockaddr_in *)&(ifr[i].ifr_addr);
            // mask some interface noused, eg. localhost
            if (strcmp("127.0.0.1", inet_ntoa(addr->sin_addr)) == 0) {
                continue;
            }
            l = sizeof(struct sockaddr_in);
            setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, (void *)addr, l);
            sendto(sock, MSG, sizeof(MSG), 0, (struct sockaddr *)&mult_addr, l);
            printf("SEND to : %s buf: %s\n", inet_ntoa(addr->sin_addr), MSG);
        }
        printf("---------------------\n");
        if (getchar() == 'q') {
            break;
        }
    }

    close(sock);
    return 0;
}
