#include <iostream>
#include <string>
#include <fstream>


int main(int argc, char **argv)
{
    const char *filename = "/tmp/test.txt";
    if (argc == 2) {
        filename = argv[1];
    }
    std::ifstream ifs(filename, std::ifstream::in);

    // read one by one
    // char c = ifs.get();
    // while(ifs.good()) {
    //     std::cout << c;
    //     c = ifs.get();
    // }

    // read line by line
    char buf[256] = {0};
    std::string lastline;
    while(ifs.good()) {
        ifs.getline(buf, 256);
        std::cout << buf << std::endl;
        if (!std::string(buf).empty()) {
            lastline = buf;
        }
    }
    std::cout << "lastline: " << lastline << std::endl;

    if (ifs.eof()) {
        std::cout << "end file" << std::endl;
    }
    return 0;
}
