#pragma once

#include <iostream>

class RealSubject
{
public:

    RealSubject()
    {
        std::cout << "RealSubject::RealSubject()" << std::endl;
    }

    void request ()
    {
        std::cout << "RealSubject::request()" << std::endl;
    }
};

