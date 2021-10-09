#pragma once

#include <memory>

#include "RefinedAbstraction.h"

#include "ConcreteImplementatorA.h"
#include "ConcreteImplementatorB.h"

class Client
{
public:

    void doSomething()
    {
        std::shared_ptr<Implementator> impA = std::make_shared<ConcreteImplementatorA>();
        std::shared_ptr<Implementator> impB = std::make_shared<ConcreteImplementatorB>();

        std::shared_ptr<Abstraction> a = std::make_shared<RefinedAbstraction>( impA );

        a->operation();
    }
};

