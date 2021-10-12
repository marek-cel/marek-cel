#include "ConcreteMediator.h"

int main( int argc, char *argv[] )
{
    ConcreteMediator cm;
    cm.invokeEventA();
    cm.invokeEventB();

    return 0;
}
