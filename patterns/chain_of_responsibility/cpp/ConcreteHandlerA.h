#pragma once

#include <iostream>

#include "Handler.h"

class ConcreteHandlerA : public Handler
{
public:

    ConcreteHandlerA() : Handler() {}

    ConcreteHandlerA( std::weak_ptr<Handler> successor ) :
        Handler( successor )
    {}

    void handleRequest ()
    {
        std::cout << "ConcreteHandlerA::handleRequest()" << std::endl;

        if ( checkIfHandled() )
        {
            std::cout << "ConcreteHandlerA: REQUEST HANDLED" << std::endl;
        }
        else
        {
            if ( !_successor.expired() )
            {
                std::shared_ptr<Handler> h = _successor.lock();
                h->handleRequest();
            }
        }
    }

private:

    bool checkIfHandled()
    {
        return false;
    }
};

