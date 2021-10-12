#pragma once

#include <iostream>

#include "Colleague.h"

class ConcreteColleagueB : public Colleague
{
public:

    ConcreteColleagueB( Mediator *mediator ) :
        Colleague( mediator )
    {}

    void handleEvent()
    {
        std::cout << "ConcreteColleagueB::handleEvent()" << std::endl;
        changed();
    }

    void doSomething()
    {
        std::cout << "ConcreteColleagueB::doSomething()" << std::endl;
    }
};

