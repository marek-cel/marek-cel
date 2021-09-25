#pragma once

#include <memory>

class Observer
{
public:

    virtual void update() = 0;
};

using ObserverPtr = std::shared_ptr<Observer>;
