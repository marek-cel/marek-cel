#pragma once

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

class Singleton final
{
public:

    static Singleton& getInstance()
    {
        static Singleton instance {};
        return instance;
    }

    void doSomething()
    {
        std::cout << "Singleton::doSomething()" << std::endl;
    }

private:

    Singleton() = default;
    Singleton( const Singleton& ) = delete;
    Singleton( Singleton && ) = delete;
    Singleton& operator=( const Singleton& ) = delete;
    Singleton& operator=( Singleton&& ) = delete;
};
