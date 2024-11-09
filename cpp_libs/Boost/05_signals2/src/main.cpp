#include <boost/function.hpp>
#include <iostream>

void hello() {
    std::cout << "Hello, world!" << std::endl;
}

int main() {
    boost::function<void()> f = &hello;
    f();
    return 0;
}