#pragma once

#include <iostream>

#include "Observer.h"

class ConcreteObserver2 : public Observer
{
public:

    virtual void update() override
    {
        std::cout << "Observer2" << std::endl;
    }
};
