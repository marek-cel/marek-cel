#pragma once

#include <algorithm>
#include <iostream>

#include "Strategy.h"

class StrategyMax : public Strategy
{
public:

    virtual void execute( std::vector< int > data ) override
    {
        std::vector<int>::iterator result = std::max_element( data.begin(), data.end() );
        std::cout << *result << std::endl;
    }
};
