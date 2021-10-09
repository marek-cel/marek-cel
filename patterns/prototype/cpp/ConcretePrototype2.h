#pragma once

#include <iostream>

#include "Prototype.h"

class ConcretePrototype2 : public Prototype
{
public:

    ConcretePrototype2() = default;
    ConcretePrototype2( const ConcretePrototype2& ) = default;

    ConcretePrototype2( int a )
    {
        _a = a;
    }

    Prototype* clone () override
    {
        return new ConcretePrototype2( *this );
    }

    void doSomething() override
    {
        std::cout << "ConcretePrototype2::doSomething() " << _a << std::endl;
    }

private:

    int _a;
};

