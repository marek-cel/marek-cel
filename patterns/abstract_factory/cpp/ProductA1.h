#pragma once

#include <iostream>

#include "AbstractProductA.h"

class ProductA1 : public AbstractProductA
{
public:

    ProductA1() {}

    virtual void doSomething()
    {
        std::cout << "ProductA1::doSomething()" << std::endl;
    }
};
