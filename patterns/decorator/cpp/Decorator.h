#pragma once

#include <memory>

#include "Component.h"

class Decorator : public Component
{
    std::shared_ptr<Component> _component;

public:

    Decorator( std::shared_ptr<Component> component )
    {
        _component = component;
    }

    void operation ()
    {
        std::cout << "Decorator::operation()" << std::endl;
        _component->operation();
    }
};

