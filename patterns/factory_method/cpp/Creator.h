#pragma once

#include "Product.h"

class Creator
{
public:
    virtual Product* factoryMethod () = 0;

    void operation ()
    {
        Product *product = factoryMethod();
        product->doSomething();
    }
};

