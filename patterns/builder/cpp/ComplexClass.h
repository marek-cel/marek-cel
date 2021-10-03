#pragma once

#include <iostream>
#include <memory>

#include "ComponentA.h"
#include "ComponentB.h"

class ComplexClass
{
public:

    ComplexClass() {}

    void addComponentA( std::weak_ptr<ComponentA> componentA )
    {
        _componentA = componentA;
    }

    void addComponentB( std::weak_ptr<ComponentB> componentB )
    {
        _componentB = componentB;
    }

    void doSomething()
    {
        std::cout << "ComplexClass::doSomething()" << std::endl;
    }

private:

    std::weak_ptr<ComponentA> _componentA;
    std::weak_ptr<ComponentB> _componentB;
};
