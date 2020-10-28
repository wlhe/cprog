#include <cstddef>
#include <iostream>

struct Storage {
    char      a;
    int       b;
    double    c;
    long long d;
};

struct alignas(std::max_align_t) AlignasStorage {
    char      a;
    int       b;
    double    c;
    long long d;
};

int main() {
    std::cout << alignof(Storage) << std::endl;
    std::cout << alignof(AlignasStorage) << std::endl;
    std::cout << sizeof(Storage) << std::endl;
    std::cout << sizeof(AlignasStorage) << std::endl;
    std::cout << sizeof(std::max_align_t) << std::endl;
    return 0;
}