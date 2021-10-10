#pragma once

#include <iostream>

#include "Command.h"
#include "ReceiverA.h"

class ConcreteCommandA : public Command
{
public:

    ConcreteCommandA( ReceiverAPtr recv )
    {
        _recv = recv;
    }

    virtual void execute() override
    {
        std::cout << "ConcreteCommandA::execute()" << std::endl;
        _recv->actionA();
    }

private:

    ReceiverAPtr _recv;
};
