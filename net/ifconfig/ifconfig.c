#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

int restart_net_if(char *net_if)
{
    struct ifreq ifr;
    int sockfd = 0;
    int ret = 0;
    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, net_if, sizeof(ifr.ifr_name));

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if ((ret = ioctl(sockfd, SIOCGIFFLAGS, &ifr)) < 0) {
        printf("ioctl SIOCGIFFLAGS error!\n");
        goto err;
    }

    printf("\nRestarting interface %s\n\n", net_if);

    ifr.ifr_flags &= (~IFF_UP);
    if ((ret = ioctl(sockfd, SIOCSIFFLAGS, &ifr)) < 0) {
        printf("ioctl SIOCSIFFLAGS error!\n");
        goto err;
    }
    sleep(1);
    ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);
    if ((ret = ioctl(sockfd, SIOCSIFFLAGS, &ifr)) < 0) {
        printf("ioctl SIOCSIFFLAGS error!\n");
        goto err;
    }

err:
    close(sockfd);

    return ret;
}

int get_mac_address(const char *net_inter, char *address, int size)
{
    struct ifreq struReq;
    int socketfd = 0;
    memset(&struReq, 0x00, sizeof(struct ifreq));
    strncpy(struReq.ifr_name, net_inter, sizeof(struReq.ifr_name));

    socketfd = socket(PF_INET, SOCK_STREAM, 0);

    if (-1 == ioctl(socketfd, SIOCGIFHWADDR, &struReq)) {
        printf("ioctl hwaddr error!\n");
        close(socketfd);
        return -1;
    }

    strcpy(address, ether_ntoa((struct ether_addr *)struReq.ifr_hwaddr.sa_data));
    close(socketfd);
    return 0;
}

int get_all_ip(void)
{
    int ret = -1;
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);

    struct ifreq ifVec[5];
    struct ifconf ifConf;
    ifConf.ifc_req = ifVec;
    ifConf.ifc_len = sizeof(ifVec);
    struct sockaddr_in *pad = NULL;

    if ((ret = ioctl(sockfd, SIOCGIFCONF, &ifConf)) < 0) {
        printf("ioctl SIOCGIFCONF error\n");
        return 0;
    }
    for (unsigned int i = 0; i < (ifConf.ifc_len / sizeof(struct ifreq)); i++) {
        pad = (struct sockaddr_in *)&(ifVec[i].ifr_addr);
        printf("%s %s\n", ifVec[i].ifr_name, inet_ntoa(pad->sin_addr));

        ret = 0;
    }
    return ret;
}

unsigned int get_ip_address(const char *net_inter, char *address)
{
    struct ifreq ifr;
    int socketfd = 0, ret = 0;
    memset(&ifr, 0x00, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, net_inter, sizeof(ifr.ifr_name));
    socketfd = socket(PF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        printf("socket error\n");
        return 0;
    }
    if ((ret = ioctl(socketfd, SIOCGIFADDR, &ifr)) < 0) {
        printf("ioctl ip address error!\n");
        close(socketfd);
        return 0;
    }
    close(socketfd);

    if (address != NULL) {
        strcpy((char *)address, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    }

    return (((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr);
}

char eth[16] = "eth0";
char mac[32] = {0};
char ip[32] = {0};

int main()
{
    get_all_ip();
    get_mac_address(eth, mac, 32);
    printf("%s mac: %s\n", eth, mac);
    restart_net_if(eth);
    get_ip_address("wlan0", ip);
    printf("wlan0 ip %s\n", ip);
    return 0;
}