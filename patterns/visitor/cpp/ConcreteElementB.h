#pragma once

#include <iostream>

#include "Element.h"

class ConcreteElementB : public Element
{
public:

    void accept ( Visitor *v )
    {
        v->visitConcreteElementB(this);
    }

    void operationB ()
    {
        std::cout << "ConcreteElementB::operationB()" << std::endl;
    }
};

