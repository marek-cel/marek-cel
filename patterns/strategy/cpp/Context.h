#pragma once

#include <vector>

#include "Strategy.h"

class Context
{
public:

    void contextInterface()
    {
        _strategy->algorithmInterface();
    }

    void setStrategy( StrategyPtr strategy )
    {
        _strategy = strategy;
    }

private:

    StrategyPtr _strategy;
};
