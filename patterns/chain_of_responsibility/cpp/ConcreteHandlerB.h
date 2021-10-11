#pragma once

#include <iostream>

#include "Handler.h"

class ConcreteHandlerB : public Handler
{
public:

    ConcreteHandlerB() : Handler() {}

    ConcreteHandlerB( std::weak_ptr<Handler> successor ) :
        Handler( successor )
    {}

    void handleRequest ()
    {
        std::cout << "ConcreteHandlerB::handleRequest()" << std::endl;

        if ( checkIfHandled() )
        {
            std::cout << "ConcreteHandlerB: REQUEST HANDLED" << std::endl;
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

