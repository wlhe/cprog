#include <iostream> // std::cout
#include <utility>  // std::move
#include <vector>   // std::vector
#include <string>   // std::string

class A
{
public:
    int *pointer;
    A() : pointer(new int(1))
    {
        std::cout << "构造" << pointer << std::endl;
    }
    A(A &a) : pointer(new int(*a.pointer))
    {
        std::cout << "拷贝" << pointer << std::endl;
    } // 无意义的对象拷贝
    A(A &&a) : pointer(a.pointer)
    {
        a.pointer = nullptr;
        std::cout << "移动" << pointer << std::endl;
    }
    ~A()
    {
        std::cout << "析构" << pointer << std::endl;
        delete pointer;
    }
};
// 防止编译器优化
A return_rvalue(bool test)
{
    A a, b;
    if (test)
        return a; // 等价于 static_cast<A&&>(a);
    else
        return b; // 等价于 static_cast<A&&>(b);
}

void test_move()
{
    A obj = return_rvalue(false);
    std::cout << "obj:" << std::endl;
    std::cout << obj.pointer << std::endl;
    std::cout << *obj.pointer << std::endl;

    A obj2 = return_rvalue(true);
    std::cout << "obj:" << std::endl;
    std::cout << obj2.pointer << std::endl;
    std::cout << *obj2.pointer << std::endl;
}

int test_move2()
{

    std::string str = "Hello world.";
    std::vector<std::string> v;

    // 将使用 push_back(const T&), 即产生拷贝行为
    v.push_back(str);
    // 将输出 "str: Hello world."
    std::cout << "str: " << str << std::endl;

    // 将使用 push_back(const T&&), 不会出现拷贝行为
    // 而整个字符串会被移动到 vector 中，所以有时候 std::move 会用来减少拷贝出现的开销
    // 这步操作后, str 中的值会变为空
    v.push_back(std::move(str));
    // 将输出 "str: "
    std::cout << "str: " << str << std::endl;

    std::string str2 = "Hello world 222.";
    v.emplace_back(str2);
    std::cout << "str2: " << str2 << std::endl;

    for (auto v1 : v)
    {
        std::cout << v1 << std::endl;
    }

    std::vector<A> va;
    va.push_back(A());
    va.emplace_back(A());

    return 0;
}

void reference(int& v) {
    std::cout << "左值" << std::endl;
}
void reference(int&& v) {
    std::cout << "右值" << std::endl;
}
template <typename T>
void pass(T&& v) {
    std::cout << "普通传参:";
    reference(v); // 始终调用 reference(int&)

    std::cout << "       std::move 传参: ";
    reference(std::move(v));
    std::cout << "    std::forward 传参: ";
    reference(std::forward<T>(v));
    std::cout << "static_cast<T&&> 传参: ";
    reference(static_cast<T&&>(v));
}
int test_move3() {
    std::cout << "传递右值:" << std::endl;
    pass(1); // 1是右值, 但输出是左值

    std::cout << "传递左值:" << std::endl;
    int l = 1;
    pass(l); // l 是左值, 输出左值

    return 0;
}

int main()
{
    // test_move();
    // test_move2();
    test_move3();
    return 0;
}