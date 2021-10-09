#pragma once

#include <iostream>

#include "Prototype.h"

class ConcretePrototype1 : public Prototype
{
public:

    ConcretePrototype1() = default;
    ConcretePrototype1( const ConcretePrototype1& ) = default;

    ConcretePrototype1( int a )
    {
        _a = a;
    }

    Prototype* clone () override
    {
        return new ConcretePrototype1( *this );
    }

    void doSomething() override
    {
        std::cout << "ConcretePrototype1::doSomething() " << _a << std::endl;
    }

private:

    int _a;
};

