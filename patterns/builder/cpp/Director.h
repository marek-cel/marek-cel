#pragma once

#include "Builder.h"

class Director
{
public:

    Director( std::weak_ptr<Builder> builder )
    {
        if ( !builder.expired() )
        {
            _builder = builder.lock();
        }
    }

    void construct()
    {
        _builder->buildProduct();
        _builder->buildPartA();
        _builder->buildPartB();

        ComplexClass *cc = _builder->getProduct();

        cc->doSomething();
    }

private:

    std::shared_ptr<Builder> _builder;
};
