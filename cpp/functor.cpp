//
#include <functional>
#include <iostream>

int func(int a)
{
    std::cout << "a: " << a << std::endl;
    return 1;
}

int main(int argc, char **argv)
{
    std::function<int (int)> a = std::bind(func, std::placeholders::_1);
    a(1);
    return 0;
}