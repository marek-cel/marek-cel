#pragma once

#include <iostream>

#include "Command.h"
#include "ReceiverB.h"

class ConcreteCommandB : public Command
{
public:

    ConcreteCommandB( ReceiverBPtr recv )
    {
        _recv = recv;
    }

    virtual void execute() override
    {
        std::cout << "ConcreteCommandB::execute()" << std::endl;
        _recv->actionB();
    }

private:

    ReceiverBPtr _recv;
};
