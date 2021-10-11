#include <iostream>

#include "Context.h"

#include "ConcreteStrategyA.h"
#include "ConcreteStrategyB.h"
#include "ConcreteStrategyC.h"

int main( int argc, char *argv[] )
{
    Context context;

    StrategyPtr sa = std::make_shared<ConcreteStrategyA>();
    StrategyPtr sb = std::make_shared<ConcreteStrategyB>();
    StrategyPtr sc = std::make_shared<ConcreteStrategyC>();

    context.setStrategy( sa );
    context.contextInterface();

    context.setStrategy( sb );
    context.contextInterface();

    context.setStrategy( sc );
    context.contextInterface();

    return 0;
}
