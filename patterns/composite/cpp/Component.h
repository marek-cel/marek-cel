#pragma once

#include <memory>

class Component
{
public:

    virtual void doSomething() = 0;
};

using ComponentPtr = std::shared_ptr<Component>;
