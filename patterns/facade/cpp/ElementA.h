#pragma once

#include <iostream>

class ElementA
{
public:

    ElementA( int x )
    {
        _x = x;
    }

    void doSomething()
    {
        std::cout << "ElementA " << _x << std::endl;
    }

private:

    int _x;
};
