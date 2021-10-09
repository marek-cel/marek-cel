#pragma once

#include "AbstractProductA.h"
#include "AbstractProductB.h"

class AbstractFactory
{
public:

    virtual AbstractProductA* createProductA() = 0;
    virtual AbstractProductB* createProductB() = 0;
};
