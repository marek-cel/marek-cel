#pragma once

#include "ComplexClass.h"

class Builder
{
public:

    virtual void buildProduct() {}
    virtual void buildPartA() {}
    virtual void buildPartB() {}

    ComplexClass* getProduct() { return nullptr; }

protected:

    Builder() {}
};
