#include <iostream>

#include "Director.h"
#include "ConcreteBuilder.h"

int main( int argc, char *argv[] )
{
    Director dir( std::make_shared<ConcreteBuilder>() );
    dir.construct();

    return 0;
}
