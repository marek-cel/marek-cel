#pragma once

#include <iostream>

#include "Implementator.h"

class ConcreteImplementatorA : public Implementator
{
public:
    void operationImp ()
    {
        std::cout << "ConcreteImplementatorA::operationImp()" << std::endl;
    }
};

