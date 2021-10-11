#pragma once

#include <vector>

#include "Observer.h"

class Subject
{
public:
    
    void attach( ObserverPtr observer )
    {
        _observers.push_back( observer );
    }

    void notify()
    {
        for ( auto observer : _observers )
        {
            observer->update();
        }
    }

private:

    std::vector<ObserverPtr> _observers;
};
