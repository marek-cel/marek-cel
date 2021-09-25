#pragma once

#include <memory>

#include "ElementA.h"
#include "ElementB.h"
#include "ElementC.h"

class Facade
{
public:

    Facade()
    {
        _elementA = std::make_shared<ElementA>( 1 );
        _elementB = std::make_shared<ElementB>( 2 );
        _elementC = std::make_shared<ElementC>( 3 );
    }

    void doSomething()
    {
        _elementA->doSomething();
        _elementB->doSomething();
        _elementC->doSomething();
    }

private:

    std::shared_ptr<ElementA> _elementA;
    std::shared_ptr<ElementB> _elementB;
    std::shared_ptr<ElementC> _elementC;
};
