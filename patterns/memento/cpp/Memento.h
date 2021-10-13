#pragma once

class Memento
{
private:

    friend class Originator;

    int getState ()
    {
        return _state;
    }

    void setState ( int state )
    {
        _state = state;
    }

private:

    int _state;
};

