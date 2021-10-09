#pragma once

#include "Creator.h"
#include "ConcreteProduct.h"

class ConcreteCreator : public Creator
{
public:

    Product* factoryMethod ()
    {
        return new ConcreteProduct;
    }
};

