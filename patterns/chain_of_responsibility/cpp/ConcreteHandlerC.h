#pragma once

#include <iostream>

#include "Handler.h"

class ConcreteHandlerC : public Handler
{
public:

    ConcreteHandlerC() : Handler() {}

    ConcreteHandlerC( std::weak_ptr<Handler> successor ) :
        Handler( successor )
    {}

    void handleRequest ()
    {
        std::cout << "ConcreteHandlerC::handleRequest()" << std::endl;

        if ( checkIfHandled() )
        {
            std::cout << "ConcreteHandlerC: REQUEST HANDLED" << std::endl;
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
        return true;
    }
};

