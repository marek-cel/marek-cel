#pragma once

#include <iostream>
#include <memory>

#include "Builder.h"

class ConcreteBuilder : public Builder
{
public:

    virtual void buildProduct()
    {
        std::cout << "ConcreteBuilder::buildProduct()" << std::endl;
        _product = std::make_shared<ComplexClass>();
    }

    virtual void buildPartA()
    {
        std::cout << "ConcreteBuilder::buildPartA()" << std::endl;
        _product->addComponentA( std::make_shared<ComponentA>() );
    }

    virtual void buildPartB()
    {
        std::cout << "ConcreteBuilder::buildPartB()" << std::endl;
        _product->addComponentB( std::make_shared<ComponentB>() );
    }

    ComplexClass* getProduct()
    {
        return _product.get();
    }

private:

    std::shared_ptr<ComplexClass> _product;
};
