#include <iostream>
#include <boost/version.hpp>

#include <ClassA.h>

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

    std::cout << std::endl;
    std::cout << "Boost version: " << BOOST_VERSION / 100000 << "."
              << BOOST_VERSION / 100 % 1000 << "." << BOOST_VERSION % 100 << std::endl;


    ClassA a;
    std::cout << std::endl;
    std::cout << "One= " << a.getOne() << std::endl;
    std::cout << "Two= " << a.getTwo() << std::endl;
    std::cout << "Six= " << a.getSix() << std::endl;
    std::cout << "Ten= " << a.getTen() << std::endl;

    return 0;
}