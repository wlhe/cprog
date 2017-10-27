#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 1234
#define BACKLOG 1

#define RECVMAX 64
#define IP_ADDR "192.168.1.149"
//#define IP_ADDR "192.168.1.135"

char recvbuf[RECVMAX];
int recv_num = 0;
char sendbuf[] = "p\n";
int main(int argc, char *argv[])
{
    int sockfd, num;
    struct hostent *he;
    struct sockaddr_in server;
    /*    if (argc!=2)
            {
           printf("Usage:%s <IP Address>\n",argv[0]);
           exit(1);
            }
            if((he = gethostbyname(argv[1])) == NULL)
            {
           printf("gethostbyname()error\n");
           exit(1);
        }
    */

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("socket()error\n");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    //	server.sin_addr = *((struct in_addr *)he->h_addr);
    server.sin_addr.s_addr = inet_addr(IP_ADDR);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        printf("connect() error\n");
        exit(1);
    }
    /*	if((recv_num = recv(sockfd,recvbuf,RECVMAX,0)) == -1)
            {
           printf("recv() error\n");
           exit(1);
        }
    */
    recvbuf[recv_num] = '\0';
    printf("Server Message: %s\n", recvbuf);
    send(sockfd, argv[1], 1, 0);
    close(sockfd);
    return 0;
}
