#pragma once

#include "Adaptee.h"
#include "Target.h"

class Adapter : public Target
{
public:

    virtual void request() override
    {
        _adaptee.specificRequest();
    }

private:

    Adaptee _adaptee;
};
