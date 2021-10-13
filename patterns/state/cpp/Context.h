#pragma once

#include <memory>

#include "ConcreteStateA.h"
#include "ConcreteStateB.h"

class Context
{
public:

    Context()
    {
        setStateA();
    }

    void request()
    {
        _state->handle();
    }

    void setStateA()
    {
        _state = std::make_shared<ConcreteStateA>();
    }

    void setStateB()
    {
        _state = std::make_shared<ConcreteStateB>();
    }

private:

    std::shared_ptr<State> _state;
};

