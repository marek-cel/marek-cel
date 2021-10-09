#pragma once

#include <iostream>

#include "AbstractProductB.h"

class ProductB2 : public AbstractProductB
{
public:

    ProductB2() {}

    virtual void doSomething()
    {
        std::cout << "ProductB2::doSomething()" << std::endl;
    }
};
