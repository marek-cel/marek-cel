#pragma once

#include <vector>

#include "Strategy.h"

class Context
{
public:

    void doSomething()
    {
        _strategy->execute( _data );
    }

    void setStrategy( StrategyPtr strategy )
    {
        _strategy = strategy;
    }

private:

    StrategyPtr _strategy;

    std::vector< int > _data { 1, 2, 3, 4 };
};
