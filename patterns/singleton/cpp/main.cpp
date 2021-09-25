#include <iostream>

#include "Singleton.h"

int main( int argc, char *argv[] )
{
    Singleton::getInstance().doSomething();
    return 0;
}
