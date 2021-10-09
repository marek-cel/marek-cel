#pragma once

#include <iostream>

#include "AbstractProductB.h"

class ProductB1 : public AbstractProductB
{
public:

    ProductB1() {}

    virtual void doSomething()
    {
        std::cout << "ProductB1::doSomething()" << std::endl;
    }
};
