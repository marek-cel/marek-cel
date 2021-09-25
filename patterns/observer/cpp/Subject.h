#pragma once

#include <vector>

#include "Observer.h"

class Subject
{
public:
    
    void addObserver( ObserverPtr observer )
    {
        _observers.push_back( observer );
    }
    
protected:

    void notifyObservers()
    {
        for ( auto observer : _observers )
        {
            observer->update();
        }
    }

private:

    std::vector<ObserverPtr> _observers;
};
