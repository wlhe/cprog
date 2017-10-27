#include "tcpserver.h"

TCPServer::TCPServer()
{
    port = PORT_DEFAULT;
    // address = NULL;
    connected = false;
}
TCPServer::TCPServer(int pt) : port(pt)
{
    // address = NULL;
    connected = false;
}
TCPServer::TCPServer(int pt, std::string address) : port(pt), address(address)
{
    connected = false;
}

int TCPServer::start()
{
    struct sockaddr_in server, client;
    int serverfd, clientfd;

    if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Create socket failed.\n");
        return -1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (address.size() > 0) {
        server.sin_addr.s_addr = inet_addr(address.c_str());
    } else {
        server.sin_addr.s_addr = INADDR_ANY;
    }

    int opt = 1;
    if ((setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) < 0) {
        perror("Setsockopt error.\n");
        return -1;
    }

    if (bind(serverfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Bind error.\n");
        return -1;
    }

    if (listen(serverfd, 5) == -1) {
        perror("Listen error.\n");
        return -1;
    }

    socklen_t len = sizeof(client);
    clientfd = accept(serverfd, (struct sockaddr *)&client, &len);
    if (clientfd == -1) {
        perror("Accept error.\n");
        return -1;
    }

    connected = true;
    sockfd = clientfd;

    return sockfd;
}

int TCPServer::stop()
{
    if (sockfd > 0) {
        close(sockfd);
        sockfd = -1;
        connected = false;
    }
}

int TCPServer::Send(char *buf, int len)
{
    return send(sockfd, buf, len, 0);
}
int TCPServer::Receive(char *buf, int len)
{
    return recv(sockfd, buf, len, 0);
}

int TCPServer::isConnected()
{
    return connected;
}
