#ifndef ABSTRACTCLASS_H_
#define ABSTRACTCLASS_H_

////////////////////////////////////////////////////////////////////////////////

class AbstractClass
{
public:

    AbstractClass();

    virtual ~AbstractClass();

    virtual int getOne() = 0;

    int getTwo();

protected:

    int *_foo { nullptr };
};

////////////////////////////////////////////////////////////////////////////////

#endif // ABSTRACTCLASS_H_
