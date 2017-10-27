
#include "tcpserver.h"

char sbuf[] = "Server to Client\n";
char rbuf[100];

int main(int argc, char *argv[])
{
    TCPServer *server = new TCPServer(1234);

    printf("This is Server!\n");

    server->start();
    printf("A client is connected,\n");


    int r = server->Receive(rbuf, 100);
    rbuf[r] = '\0';
    printf("Server:Recieve from client:%s", rbuf);

    server->Send(sbuf, sizeof(sbuf));

    server->stop();

    return 0;
}
