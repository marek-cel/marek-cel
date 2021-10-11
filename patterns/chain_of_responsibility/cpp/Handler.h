#pragma once

#include <memory>

#include "Client.h"

class Handler
{
public:

    Handler() {}

    Handler( std::weak_ptr<Handler> successor )
    {
        _successor = successor;
    }

    virtual ~Handler() {}

    virtual void handleRequest () = 0;

protected:

    std::weak_ptr<Handler> _successor;
};

