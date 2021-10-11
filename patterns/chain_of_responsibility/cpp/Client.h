#pragma once

#include "ConcreteHandlerA.h"
#include "ConcreteHandlerB.h"
#include "ConcreteHandlerC.h"

class Client
{
public:

    void doSomething()
    {
        std::shared_ptr<Handler> hc = std::make_shared<ConcreteHandlerC>();
        std::shared_ptr<Handler> hb = std::make_shared<ConcreteHandlerB>( hc );
        std::shared_ptr<Handler> ha = std::make_shared<ConcreteHandlerA>( hb );

        ha->handleRequest();
    }
};

