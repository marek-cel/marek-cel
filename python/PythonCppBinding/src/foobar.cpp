#include <foobar.h>

#include <iostream>

FooBar::FooBar()
{
    std::cout << "Hello, World!, from C++" << std::endl;
}

FooBar::~FooBar()
{
    std::cout << "Goodbye, World!, from C++" << std::endl;
}

void FooBar::greet()
{
    std::cout << "Greetings, from C++" << std::endl;
}
