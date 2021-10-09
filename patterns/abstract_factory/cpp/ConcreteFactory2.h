#pragma once

#include "AbstractFactory.h"

#include "ProductA2.h"
#include "ProductB2.h"

class ConcreteFactory2 : public AbstractFactory
{
public:

    virtual AbstractProductA* createProductA()
    {
        return new ProductA2();
    }

    virtual AbstractProductB* createProductB()
    {
        return new ProductB2();
    }
};
