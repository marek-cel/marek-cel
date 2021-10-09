#pragma once

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

class Singleton
{
public:

    static Singleton* getInstance()
    {
        if ( _instance == nullptr )
        {
            _instance = new Singleton();
        }

        return _instance;
    }

    void doSomething()
    {
        std::cout << "Singleton::doSomething()" << std::endl;
    }

protected:

    Singleton() = default;
    Singleton( const Singleton& ) = delete;
    Singleton( Singleton && ) = delete;
    Singleton& operator=( const Singleton& ) = delete;
    Singleton& operator=( Singleton&& ) = delete;

private:

    static Singleton *_instance;
};
