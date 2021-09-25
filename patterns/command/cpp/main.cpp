#include <memory>

#include "Macro.h"
#include "Hello.h"
#include "World.h"

int main( int argc, char *argv[] )
{
    std::unique_ptr<Macro> macro = std::make_unique<Macro>();

    CommandPtr hello = std::make_shared<Hello>();
    CommandPtr world = std::make_shared<World>();

    macro->addCommand( hello );
    macro->addCommand( world );

    macro->execute();

    return 0;
}
