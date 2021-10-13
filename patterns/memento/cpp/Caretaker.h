#pragma once

#include "Originator.h"

class Caretaker
{
public:

    void doSomething()
    {
        Originator o;
        o.printState();

        Memento *m = o.createMemento();

        o.operation();
        o.printState();

        o.setMemento( m );
        o.printState();
    }
};

