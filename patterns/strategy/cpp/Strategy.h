#pragma once

#include <memory>
#include <vector>

class Strategy
{
public:

    virtual void execute( std::vector< int > data ) = 0;
};

using StrategyPtr = std::shared_ptr<Strategy>;
