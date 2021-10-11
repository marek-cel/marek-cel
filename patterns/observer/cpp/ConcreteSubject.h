#pragma once

#include "Subject.h"

class ConcreteSubject : public Subject
{
public:

    int getState() { return _subjectState; }

    void setState( int state )
    {
        _subjectState = state;
        notify();
    }

private:

    int _subjectState { 0 };
};

using ConcreteSubjectPtr = std::shared_ptr<ConcreteSubject>;
