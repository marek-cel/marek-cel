#pragma once

#include "Flyweight.h"
#include "Client.h"

class UnsheredConcreteFlyweight : public Flyweight
{
public:

    void operation ( int extrinsicState );

private:
    int _allState;

};
