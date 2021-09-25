#pragma once

#include <iostream>

class ElementB
{
public:

    ElementB( long x )
    {
        _x = x;
    }

    void doSomething()
    {
        std::cout << "ElementB " << _x << std::endl;
    }

private:

    long _x;
};
