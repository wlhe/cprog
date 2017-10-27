

#include "tcpclient.h"

#define PORT 1234
#define BACKLOG 1

#define RECVMAX 64
//#define IP_ADDR "192.168.1.140"
#define IP_ADDR "127.0.0.1"

char recvbuf[RECVMAX];
int recv_num = 0;
char sendbuf[] = "Client to Server\n";

int main(int argc, char *argv[])
{
    TCPClient *client = new TCPClient(1234, IP_ADDR);

    printf("This is Client~\n");

    client->connect();
    client->Send(sendbuf, sizeof(sendbuf));
    recv_num = client->Receive(recvbuf, RECVMAX);
    recvbuf[recv_num] = '\0';
    printf("Client :%s\n", recvbuf);
    client->disconnect();

    return 0;
}