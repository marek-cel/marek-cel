#pragma once

#include <iostream>
#include <memory>

class MyClassA
{
public:

    MyClassA() = default;

    virtual ~MyClassA()
    {
        std::cout << "MyClassA::~MyClassA()" << std::endl;
    }

    void setPtr( std::shared_ptr<MyClassA> ptr )
    {
        _ptr = ptr;
    }

private:

    std::shared_ptr<MyClassA> _ptr;
};
