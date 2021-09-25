#pragma once

#include <iostream>

#include "Command.h"

class Hello : public Command
{
public:

    virtual void execute() override
    {
        std::cout << "Hello" << std::endl;
    }
};
