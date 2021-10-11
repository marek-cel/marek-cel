#pragma once

#include <memory>
#include <vector>

class Strategy
{
public:

    virtual void algorithmInterface() = 0;
};

using StrategyPtr = std::shared_ptr<Strategy>;
