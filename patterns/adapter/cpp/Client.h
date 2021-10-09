#pragma once

#include "Adapter.h"

class Client
{
public:

    void action()
    {
        Target *t = new Adapter;
        t->request();
    }
};
