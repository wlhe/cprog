#include <iostream>
#include <memory>

void lambda_value_capture() {
    int value = 1;
    auto copy_value = [value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    std::cout << "value = " << value << std::endl;
    // 这时, stored_value == 1, 而 value == 100.
    // 因为 copy_value 在创建时就保存了一份 value 的拷贝
}

void lambda_reference_capture() {
    int value = 1;
    auto copy_value = [&value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    std::cout << "value = " << value << std::endl;
    // 这时, stored_value == 100, value == 100.
    // 因为 copy_value 保存的是引用
}


int expression_capture() {
    auto important = std::make_unique<int>(1);
    std::cout << *important << std::endl; // 1

    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
        return x+y+v1+(*v2);
    };
    std::cout << add(3,4) << std::endl; // 9
    // std::cout << *important << std::endl; // Segmentation fault (core dumped). important moved

    auto important2 = std::make_unique<int>(1);
    auto add2 = [&important2](int x, int y) -> int {
        return x+y+(*important2);
    };
    std::cout << add2(3,4) << std::endl; // 8
    std::cout << *important2 << std::endl; // 1

    auto add3 = [](auto x, auto y) {
        return x + y;
    };

    std::cout << add3(1, 2) << std::endl;
    std::cout << add3(1, 2.1) << std::endl;
    std::cout << add3(1.1, 2.2) << std::endl;


    std::cout << []{return 1+2;}() << std::endl;


    return 0;
}

int main(int argc, char **argv)
{
    lambda_value_capture();
    lambda_reference_capture();
    expression_capture();
    return 0;
}