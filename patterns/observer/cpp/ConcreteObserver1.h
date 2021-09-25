#pragma once

#include <iostream>

#include "Observer.h"

class ConcreteObserver1 : public Observer
{
public:

    virtual void update() override
    {
        std::cout << "Observer1" << std::endl;
    }
};
