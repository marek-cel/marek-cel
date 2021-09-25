#pragma once

#include <iostream>

class ElementC
{
public:

    ElementC( double x )
    {
        _x = x;
    }

    void doSomething()
    {
        std::cout << "ElementC " << _x << std::endl;
    }

private:

    double _x;
};
