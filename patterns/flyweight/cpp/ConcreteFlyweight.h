#pragma once

#include "Flyweight.h"
#include "Client.h"

class ConcreteFlyweight : public Flyweight
{
public:

    void operation ( int extrinsicState );

private:

    int _intrinsicState;
};

