#pragma once

#include "ConcretePrototype1.h"
#include "ConcretePrototype2.h"

class Client
{
public:

    void operation ()
    {
        Prototype *p1 = _cp1.clone();
        Prototype *p2 = _cp2.clone();

        p1->doSomething();
        p2->doSomething();
    }

private:

    ConcretePrototype1 _cp1 { 1 };
    ConcretePrototype2 _cp2 { 2 };
};

