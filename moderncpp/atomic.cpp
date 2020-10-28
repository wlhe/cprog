#include <thread>
#include <iostream>

int test1() {
    int a = 0;
    int flag = 0;

    std::thread t1([&]() {
        while (flag != 1);

        int b = a;
        std::cout << "b = " << b << std::endl;
    });

    std::thread t2([&]() {
        a = 5;
        flag = 1;
    });

    t1.join();
    t2.join();
    return 0;
}

#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> count = {0};

int test2() {
    std::thread t1([](){
        count.fetch_add(1);
    });
    std::thread t2([](){
        count++;        // 等价于 fetch_add
        count += 1;     // 等价于 fetch_add
    });
    t1.join();
    t2.join();
    std::cout << count << std::endl;
    return 0;
}

struct A {
    float x;
    int y;
    // long long z;
};

int test3() {
    std::atomic<A> a;
    std::cout << std::boolalpha << a.is_lock_free() << std::endl;
    return 0;
}

int main() {
    // test1();
    // test2();
    test3();
    return 0;
}