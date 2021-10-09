#pragma once

#include <iostream>

#include "AbstractProductA.h"

class ProductA2 : public AbstractProductA
{
public:

    ProductA2() {}

    virtual void doSomething()
    {
        std::cout << "ProductA2::doSomething()" << std::endl;
    }
};
