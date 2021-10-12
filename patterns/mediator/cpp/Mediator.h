#pragma once

class Colleague;

class Mediator
{
public:

    virtual ~Mediator() {}

    virtual void colleagueChanged( Colleague *colleague ) = 0;

protected:

    Mediator() {}
};

