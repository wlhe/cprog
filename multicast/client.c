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

    while (1) {
        sendto(sock, MSG, sizeof(MSG), 0, (struct sockaddr *)&mult_addr, l);
        printf("SEND to : %s buf: %s\n", inet_ntoa(mult_addr.sin_addr), MSG);

        if (getchar() == 'q') {
            break;
        }
    }

    close(sock);
    return 0;
}
