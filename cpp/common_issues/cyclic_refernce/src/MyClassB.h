#pragma once

#include <iostream>
#include <memory>

class MyClassB
{
public:

    MyClassB() = default;

    virtual ~MyClassB()
    {
        std::cout << "MyClassB::~MyClassB()" << std::endl;
    }

    void setPtr( std::weak_ptr<MyClassB> ptr )
    {
        _ptr = ptr;
    }

private:

    std::weak_ptr<MyClassB> _ptr;
};
