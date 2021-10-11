#pragma once

#include <iostream>

#include "Strategy.h"

class ConcreteStrategyA : public Strategy
{
public:

    void algorithmInterface ()
    {
        std::cout << "ConcreteStrategyA::algorithmInterface()" << std::endl;
    }
};

