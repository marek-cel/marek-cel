#pragma once

#include <memory>

#include "Client.h"
#include "Implementator.h"


class Abstraction
{
public:

    Abstraction( std::shared_ptr<Implementator> imp )
    {
        _imp = imp;
    }

    void operation ()
    {
        _imp->operationImp();
    }

private:

    std::shared_ptr<Implementator> _imp;
};

