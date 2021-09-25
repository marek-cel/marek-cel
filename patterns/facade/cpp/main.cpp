#include <memory>

#include "Facade.h"

int main( int argc, char *argv[] )
{
    std::shared_ptr<Facade> facade = std::make_shared<Facade>();
    facade->doSomething();

    return 0;
}
