#pragma once

#include <iostream>

#include "Decorator.h"

class ConcreteDecoratorA : public Decorator
{
public:

    ConcreteDecoratorA( std::shared_ptr<Component> component ) :
        Decorator ( component )
    {}

    void operation ()
    {
        Decorator::operation();
        std::cout << "ConcreteDecoratorA::operation()" << std::endl;
    }

private:

    int _addedState { 0 };
};

