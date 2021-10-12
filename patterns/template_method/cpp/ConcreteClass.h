#pragma once

#include <iostream>

#include "AbstractClass.h"

class ConcreteClass : public AbstractClass
{
protected:

    void primitiveOperation1 ()
    {
        std::cout << "ConcreteClass::primitiveOperation1()" << std::endl;
    }

    void primitiveOperation2 ()
    {
        std::cout << "ConcreteClass::primitiveOperation2()" << std::endl;
    }
};

