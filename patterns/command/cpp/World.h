#pragma once

#include <iostream>

#include "Command.h"

class World : public Command
{
public:

    virtual void execute() override
    {
        std::cout << "World" << std::endl;
    }
};
