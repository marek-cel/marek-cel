#pragma once

#include <memory>

class Component
{
public:

    virtual void operation() = 0;
};

using ComponentPtr = std::shared_ptr<Component>;
