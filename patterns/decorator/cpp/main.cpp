#include <memory>

#include "ConcreteComponent.h"
#include "ConcreteDecoratorA.h"
#include "ConcreteDecoratorB.h"

int main( int argc, char *argv[] )
{
    std::shared_ptr<Component>  cc = std::make_shared<ConcreteComponent>();
    std::shared_ptr<Component> ca = std::make_shared<ConcreteDecoratorA>( cc );
    std::shared_ptr<Component> cb = std::make_shared<ConcreteDecoratorB>( ca );

    cb->operation();

    return 0;
}
