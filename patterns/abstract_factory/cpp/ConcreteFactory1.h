#pragma once

#include "AbstractFactory.h"

#include "ProductA1.h"
#include "ProductB1.h"

class ConcreteFactory1 : public AbstractFactory
{
public:

    virtual AbstractProductA* createProductA()
    {
        return new ProductA1();
    }

    virtual AbstractProductB* createProductB()
    {
        return new ProductB1();
    }
};
