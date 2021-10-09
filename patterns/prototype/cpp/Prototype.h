#pragma once

#include "Client.h"

class Prototype
{
public:
    virtual Prototype* clone () = 0;

    virtual void doSomething() = 0;
};

