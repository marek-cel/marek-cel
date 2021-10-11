#pragma once

#include <iostream>

#include "Strategy.h"

class ConcreteStrategyB : public Strategy
{
public:

    void algorithmInterface ()
    {
        std::cout << "ConcreteStrategyB::algorithmInterface()" << std::endl;
    }
};

