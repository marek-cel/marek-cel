#pragma once

class AbstractClass
{
public:

    virtual ~AbstractClass() {}

    void templateMethod ()
    {
        // ...
        primitiveOperation1();
        // ...
        primitiveOperation2();
        // ...
    }

protected:

    virtual void primitiveOperation1 () = 0;
    virtual void primitiveOperation2 () = 0;
};

