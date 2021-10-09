#include <iostream>

#include "Singleton.h"

Singleton* Singleton::_instance = nullptr;

int main( int argc, char *argv[] )
{
    Singleton::getInstance()->doSomething();
    return 0;
}
