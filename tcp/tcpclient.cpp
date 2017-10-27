#include "tcpclient.h"


TCPClient::TCPClient()
{
    port = PORT_DEFAULT;
    address = "127.0.0.1";
    connected = false;
}

TCPClient::TCPClient(int pt, std::string address) : port(pt)
{
    this->address = address;
    connected = false;
}

int TCPClient::connect()
{
    int clientfd, num;
    struct sockaddr_in server;

    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("socket() error\n");
        return clientfd;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(address.c_str());

    if (::connect(clientfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        printf("connect() error\n");
        return -1;
    }

    connected = true;
    sockfd = clientfd;
    return sockfd;
}

int TCPClient::disconnect()
{
    if (sockfd > 0) {
        ::close(sockfd);
        connected = false;
        sockfd = -1;
    }
}
int TCPClient::getSocket()
{
    return sockfd;
}
void TCPClient::setPort(int port)
{
    this->port = port;
}
void TCPClient::setAddress(std::string address)
{
    this->address = address;
}
void TCPClient::setAddress(const char *address)
{
    this->address = address;
}


int TCPClient::Send(char *buf, int len)
{
    return ::send(sockfd, buf, len, 0);
}
int TCPClient::Receive(char *buf, int len)
{
    return ::recv(sockfd, buf, len, 0);
}

bool TCPClient::isConnected()
{
    return connected;
}