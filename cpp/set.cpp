#include <iostream>
#include <set>
#include <cstring>

int main(int argc, char **argv)
{
    // int *p = new int(10);
    int *p = (int *)malloc(10);
    for (int i = 0; i < 10; i++) {
        *(p+i) = i;
        std::cout << *(p+i) << " ";
    }
    std::cout << "end" << std::endl;

    std::set<int> s;
    s.insert(p, p+10);
    for (int i = 0; i < 10; i++) {
        *(p+i) = i * 2;
        std::cout << *(p+i) << " ";
    }
    for (auto &it : s) {
        std::cout << it << " ";
    }
    std::cout << "end2" << std::endl;
    // delete p;
    free(p);
    p = nullptr;
    return 0;
}