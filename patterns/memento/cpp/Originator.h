#pragma once

#include <iostream>

#include "Memento.h"

class Originator
{
public:

    void setMemento ( Memento *m )
    {
        _state = m->getState();
    }

    Memento* createMemento()
    {
        Memento *m = new Memento();
        m->setState( _state );
        return m;
    }

    void operation() { _state = 1; }

    void printState()
    {
        std::cout << "Originator::printState() state= " << _state << std::endl;
    }

private:

    int _state { 0 };
};

