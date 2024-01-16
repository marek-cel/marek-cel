#include <iostream>

#include <ClassA.h>

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;


    ClassA a;
    std::cout << std::endl;
    std::cout << "One= " << a.getOne() << std::endl;
    std::cout << "Two= " << a.getTwo() << std::endl;
    std::cout << "Six= " << a.getSix() << std::endl;
    std::cout << "Ten= " << a.getTen() << std::endl;

    return 0;
}