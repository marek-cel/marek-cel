#include <iostream>

#include "MyClass.h"

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

    MyClass a;
    std::cout << std::endl;
    std::cout << "One= " << a.getOne() << std::endl;
    std::cout << "Two= " << a.getTwo() << std::endl;

    return 0;
}
