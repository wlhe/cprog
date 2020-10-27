// Singleton
#include <iostream>

template <typename T>
class Singleton
{
public:
    static T &instance() {
        static T _instance;
        return _instance;
    }

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

protected:
    Singleton() = default;
    ~Singleton() = default;
};