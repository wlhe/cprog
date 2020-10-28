#include <iostream>
#include <functional>

int main() {
    [out = std::ref(std::cout << "Result from C code: " << 1)](){
        out.get() << ".\n";
    }();
    return 0;
}