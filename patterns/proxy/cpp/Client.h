#pragma once

#include <memory>

#include "Proxy.h"

class Client
{
public:

    void doSomething()
    {
        std::shared_ptr<Subject> s = std::make_shared<Proxy>();
        s->request();
        s->request();
        s->request();
    }
};

