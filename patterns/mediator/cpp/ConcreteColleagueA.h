#pragma once

#include <iostream>

#include "Colleague.h"

class ConcreteColleagueA : public Colleague
{
public:

    ConcreteColleagueA( Mediator *mediator ) :
        Colleague( mediator )
    {}

    void handleEvent()
    {
        std::cout << "ConcreteColleagueA::handleEvent()" << std::endl;
        changed();
    }

    void doSomething()
    {
        std::cout << "ConcreteColleagueA::doSomething()" << std::endl;
    }
};

