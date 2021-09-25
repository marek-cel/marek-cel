#pragma once

#include <vector>

#include "Component.h"

class Composite : public Component
{
public:

    virtual void doSomething() override
    {
        for ( auto component : _components )
        {
            component->doSomething();
        }
    }

    void add( ComponentPtr component )
    {
        _components.push_back( component );
    }

private:

    std::vector<ComponentPtr> _components;
};
