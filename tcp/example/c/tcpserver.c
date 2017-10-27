#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 1234
#define BACKLOG 1

char sendbuf[] = "Welcome to server!\n";

int main(int argc, char argv[])
{
    int listenfd, connectfd;
    struct sockaddr_in server, client;
    socklen_t addrlen;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Create socket failed.\n");
        exit(1);
    }

    int opt = SO_REUSEADDR;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Binderror.\n");
        exit(1);
    }
    if (listen(listenfd, BACKLOG) == -1) {
        perror("Listen error.\n");
        exit(1);
    }
    addrlen = sizeof(client);

    printf("Waiting for connect...\n");
    connectfd = accept(listenfd, (struct sockaddr *)&client, &addrlen);
    if (connectfd == -1) {
        perror("Accept error.\n");
        exit(1);
    }

    printf("A client is connected, ip: %s\tport:%d\n", inet_ntoa(client.sin_addr), htons(client.sin_port));

    send(connectfd, sendbuf, sizeof(sendbuf), 0);

    close(connectfd);
    close(listenfd);

    return 0;
}
