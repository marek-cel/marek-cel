#pragma once

#include "Visitor.h"

class Element
{
public:
    virtual void accept ( Visitor *v ) = 0;
};

