#pragma once

#include <iostream>

#include "State.h"

class ConcreteStateA : public State
{
public:
    void handle ()
    {
        std::cout << "ConcreteStateA::handle()" << std::endl;
    }
};

