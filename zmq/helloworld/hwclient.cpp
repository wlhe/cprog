#include <cstdio>
#include <string>

#include <zmq.hpp>

int main(int argc, char **argv)
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::req);

    printf("Connecting to hello world server...\n");
    socket.connect("tcp://localhost:5555");

    for (int i = 0; i < 10; i++) {
        zmq::message_t request(5);
        memcpy(request.data(), "Hello", 5);
        printf("Sending Hello %d\n", i);
        socket.send(request, zmq::send_flags::none);

        zmq::message_t reply;
        socket.recv(reply);
        std::string str(reply.data<char>(), reply.size());
        printf("reply: %d %s\n", int(str.size()), str.c_str());
    }
    return 0;
}