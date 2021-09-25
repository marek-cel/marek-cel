#include <memory>

#include "Composite.h"
#include "Leaf.h"

int main( int argc, char *argv[] )
{
    std::shared_ptr<Composite> root  = std::make_shared<Composite>();
    std::shared_ptr<Composite> group = std::make_shared<Composite>();

    ComponentPtr a = std::make_shared<Leaf>( "A" );
    ComponentPtr b = std::make_shared<Leaf>( "B" );
    ComponentPtr c = std::make_shared<Leaf>( "C" );

    root->add( a );
    root->add( group );

    group->add( b );
    group->add( c );

    root->doSomething();

    return 0;
}
