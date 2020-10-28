#include <iostream>

template<typename T, typename U>
auto add(T x, U y)  {
    return x+y;
}

int main(int argc, char **argv)
{
    std::cout << add<int, float>(1, 2.3f) << std::endl;
    std::cout << add(1.65656f, 2.315643454) << std::endl;

    return 0;
}