#pragma once

#include <iostream>

#include "State.h"

class ConcreteStateB : public State
{
public:
    void handle ()
    {
        std::cout << "ConcreteStateB::handle()" << std::endl;
    }
};

