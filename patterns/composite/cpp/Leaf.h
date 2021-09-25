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

    virtual void doSomething()
    {
        std::cout << "My name is " << _name << std::endl;
    }

private:

    std::string _name;
};
