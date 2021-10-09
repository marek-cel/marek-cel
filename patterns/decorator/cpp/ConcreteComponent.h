#pragma once

#include <iostream>

#include "Component.h"

class ConcreteComponent : public Component
{
public:

    void operation ()
    {
        std::cout << "ConcreteComponent::operation()" << std::endl;
    }
};

