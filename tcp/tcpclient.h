#ifndef __TCPCLIENT_H
#define __TCPCLIENT_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

class TCPClient
{
  public:
    TCPClient();
    TCPClient(int pt, std::string address);

    int connect();
    int disconnect();

    void setPort(int port);
    void setAddress(std::string address);
    void setAddress(const char *address);

    int getSocket();
    bool isConnected();

    int Send(char *buf, int len);
    int Receive(char *buf, int len);

  private:
    int port;
    const static int PORT_DEFAULT = 9999;
    std::string address;
    int sockfd;
    bool connected;
};

#endif /*__TCPCLIENT_H*/