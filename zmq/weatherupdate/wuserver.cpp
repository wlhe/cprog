#include <string>
#include <cstdio>

#include <unistd.h>

#include <zmq.hpp>

int main(int argc, char **argv)
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUB);


    return 0;
}