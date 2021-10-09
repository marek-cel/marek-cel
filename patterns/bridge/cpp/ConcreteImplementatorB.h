#pragma once

#include <iostream>

#include "Implementator.h"

class ConcreteImplementatorB : public Implementator
{
public:
    void operationImp ()
    {
        std::cout << "ConcreteImplementatorB::operationImp()" << std::endl;
    }
};

