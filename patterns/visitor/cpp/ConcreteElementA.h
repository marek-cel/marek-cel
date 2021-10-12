#pragma once

#include <iostream>

#include "Element.h"

class ConcreteElementA : public Element
{
public:

    void accept ( Visitor *v )
    {
        v->visitConcreteElementA(this);
    }

    void operationA ()
    {
        std::cout << "ConcreteElementA::operationA()" << std::endl;
    }
};

