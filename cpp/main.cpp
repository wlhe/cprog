// Test main

#include <iostream>
#include "singleton.hpp"

class Test : public Singleton<Test>
{
public:
    friend class Singleton<Test>;
    void testprint(int t)
    {
        std::cout << "test: " << t << std::endl;
    }
private:
    Test() {std::cout << __func__ << std::endl;};
    ~Test() {std::cout << __func__ << std::endl;}
};

class Test2
{
public:
    void testprint(int t)
    {
        std::cout << "test: " << t << std::endl;
    }
};

int main(int argc, char **argv)
{
    Test::instance().testprint(1);
    // Test t;
    // t.testprint(0);
    // Singleton<Test> t0;
    Singleton<Test2>::instance().testprint(2);
    // Singleton<Test2> t2;
    return 0;
}