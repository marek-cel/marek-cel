#pragma once

#include <iostream>

#include "Decorator.h"

class ConcreteDecoratorB : public Decorator
{
public:

    ConcreteDecoratorB( std::shared_ptr<Component> component ) :
        Decorator ( component )
    {}

    void operation ()
    {
        Decorator::operation();
        std::cout << "ConcreteDecoratorB::operation()" << std::endl;
        addedBehaviour();
    }

    void addedBehaviour ()
    {
        std::cout << "ConcreteDecoratorB::addedBehaviour()" << std::endl;
    }
};

