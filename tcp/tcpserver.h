
#ifndef __TCPSERVER_H
#define __TCPSERVER_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

class TCPServer
{
  public:
    TCPServer();
    TCPServer(int pt);
    TCPServer(int pt, std::string address);

    int start();
    int stop();

    int isConnected();

    int Send(char *buf, int len);
    int Receive(char *buf, int len);

  private:
    int port;
    const static int PORT_DEFAULT = 9999;
    std::string address;
    int sockfd;
    bool connected;
};

#endif /*__TCPSERVER_H*/