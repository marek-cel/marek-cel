#pragma once

#include <memory>

#include "Subject.h"
#include "RealSubject.h"

class Proxy : public Subject
{
public:

    void request ()
    {
        create();
        _realSubject->request();
    }

private:

    std::shared_ptr<RealSubject> _realSubject;

    void create()
    {
        if ( _realSubject == nullptr )
        {
            _realSubject = std::make_shared<RealSubject>();
        }
    }
};

