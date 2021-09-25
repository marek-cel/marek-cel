#pragma once

#include "WhatIHave.h"
#include "WhatIWant.h"

class Adapter : public WhatIWant
{
public:

    virtual void f() override
    {
        whatIHave.g();
        whatIHave.h();
    }

private:

    WhatIHave whatIHave;
};
