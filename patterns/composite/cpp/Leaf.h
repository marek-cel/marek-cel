#pragma once

#include <iostream>
#include <string>

#include "Component.h"

class Leaf : public Component
{
public:

    Leaf( const char *name )
    {
        _name = name;
    }

    virtual void operation() override
    {
        std::cout << "Leaf::operation() name= " << _name << std::endl;
    }

private:

    std::string _name;
};
