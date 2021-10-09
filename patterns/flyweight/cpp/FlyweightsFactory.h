#pragma once

#include "Client.h"
#include "Flyweight.h"

class FlyweightsFactory
{
public:

    Flyweight *getFlyweight ( int key);

private:

    Flyweight* _flyweights;
};

