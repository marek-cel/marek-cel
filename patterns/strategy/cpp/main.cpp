#include <iostream>

#include "Context.h"
#include "StrategyMin.h"
#include "StrategyMax.h"

int main( int argc, char *argv[] )
{
    Context context;

    StrategyPtr strategyMin = std::make_shared<StrategyMin>();
    StrategyPtr strategyMax = std::make_shared<StrategyMax>();

    context.setStrategy( strategyMin );
    context.doSomething();

    context.setStrategy( strategyMax );
    context.doSomething();

    return 0;
}
