#include <cstdio>
#include <string>
#include <sstream>

#include <zmq.hpp>

int main(int argc, char **argv)
{
    zmq::context_t context(1);

    printf("Collecting update from weather server...\n");
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5556");

    const char *filter = (argc > 1) ? argv[1] : "10001";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));

    int update_nbr = 0;
    long total_temp = 0;
    for (int i = 0; i < 100; i++) {
        zmq::message_t update;
        int seq = 0, zipcode = 0, temperature = 0, relhumidity = 0;

        subscriber.recv(update);

        sscanf(update.data<char>(), "%d %05d %d %d", &seq, &zipcode, &temperature, &relhumidity);
        total_temp += temperature;

        printf("update: %s\n", std::string(update.data<char>(), update.size()).c_str());
        printf("seq: %d zipcode %05d temp %d hum %d\n",
            seq, zipcode, temperature, relhumidity);
    }


    return 0;
}