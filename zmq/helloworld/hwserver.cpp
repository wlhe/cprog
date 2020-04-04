#include <string>
#include <cstdio>

#include <unistd.h>

#include <zmq.hpp>

int main(int argc, char **argv)
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::rep);

    socket.bind("tcp://*:5555");

    int i = 0;
    while(true) {
        zmq::message_t request;

        socket.recv(request);
        std::string restr(request.data<char>(), request.size());
        printf("Receive %d %s\n", int(restr.size()), request.data<char>());

        sleep(1);

        zmq::message_t reply(5);
        memcpy(reply.data(), "World", 5);
        socket.send(reply, zmq::send_flags::none);
    }

    return 0;
}