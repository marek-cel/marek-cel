#pragma once

#include <memory>

#include "AbstractFactory.h"

class Client
{
public:

    Client( std::weak_ptr<AbstractFactory> af )
    {
        if ( !af.expired() )
        {
            _af = af.lock();

            _productA = std::shared_ptr<AbstractProductA>( _af->createProductA() );
            _productB = std::shared_ptr<AbstractProductB>( _af->createProductB() );
        }
    }

    void doSomething()
    {
        _productA->doSomething();
        _productB->doSomething();
    }

private:

    std::shared_ptr<AbstractFactory> _af;

    std::shared_ptr<AbstractProductA> _productA;
    std::shared_ptr<AbstractProductB> _productB;
};
