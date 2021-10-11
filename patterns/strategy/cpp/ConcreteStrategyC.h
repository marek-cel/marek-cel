#pragma once

#include <iostream>

#include "Strategy.h"

class ConcreteStrategyC : public Strategy
{
public:

    void algorithmInterface ()
    {
        std::cout << "ConcreteStrategyC::algorithmInterface()" << std::endl;
    }
};

