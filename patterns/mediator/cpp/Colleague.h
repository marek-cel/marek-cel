#pragma once

#include "Mediator.h"

class Colleague
{
public:

    Colleague( Mediator *mediator )
    {
        _mediator = mediator;
    }

protected:

    Mediator* _mediator;

    void changed()
    {
        _mediator->colleagueChanged( this );
    }
};

