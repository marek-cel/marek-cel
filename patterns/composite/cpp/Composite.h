#pragma once

#include <vector>

#include "Component.h"

class Composite : public Component
{
public:

    virtual void operation() override
    {
        for ( auto component : _components )
        {
            component->operation();
        }
    }

    void add( ComponentPtr component )
    {
        _components.push_back( component );
    }

private:

    std::vector<ComponentPtr> _components;
};
