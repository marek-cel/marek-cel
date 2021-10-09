#pragma once

#include <iostream>

#include "Product.h"
#include "ConcreteCreator.h"

class ConcreteProduct : public Product
{
public:

    virtual void doSomething() override
    {
        std::cout << "ConcreteProduct::doSomething()" << std::endl;
    }
};

