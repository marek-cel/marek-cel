#pragma once

#include <iostream>

#include "Mediator.h"

#include "ConcreteColleagueA.h"
#include "ConcreteColleagueB.h"

class ConcreteMediator : public Mediator
{
public:

    ConcreteMediator()
    {
        _colleagueA = new ConcreteColleagueA( this );
        _colleagueB = new ConcreteColleagueB( this );
    }

    void invokeEventA() { _colleagueA->handleEvent(); }
    void invokeEventB() { _colleagueB->handleEvent(); }

    void colleagueChanged( Colleague *colleague )
    {
        if ( colleague == _colleagueA )
        {
            std::cout << "ConcreteMediator::colleagueChanged(Colleague*) colleagueA changed" << std::endl;
            _colleagueB->doSomething();
        }
        else if ( colleague == _colleagueB )
        {
            std::cout << "ConcreteMediator::colleagueChanged(Colleague*) colleagueB changed" << std::endl;
            _colleagueA->doSomething();
        }
    }

private:

    ConcreteColleagueA* _colleagueA;
    ConcreteColleagueB* _colleagueB;
};

