#pragma once

#include <iostream>

class Adaptee
{
public:

    void specificRequest()
    {
        std::cout << "Adaptee::specificRequest()" << std::endl;
    }
};
