#pragma once

#include <iostream>

#include "Observer.h"
#include "ConcreteSubject.h"

class ConcreteObserverA : public Observer
{
public:

    ConcreteObserverA( std::weak_ptr<ConcreteSubject> subject )
    {
        _subject = subject;
    }

    virtual void update() override
    {
        if ( !_subject.expired() )
        {
            ConcreteSubjectPtr subject = _subject.lock();
            _observerState = subject->getState();
        }

        std::cout << "ConcreteObserverA::update() _observerState= " << _observerState << std::endl;
    }

private:

    std::weak_ptr<ConcreteSubject> _subject;

    int _observerState { 0 };
};
