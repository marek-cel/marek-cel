#ifndef DERIVEDCLASS_H_
#define DERIVEDCLASS_H_

////////////////////////////////////////////////////////////////////////////////

#include <BaseClass.h>

////////////////////////////////////////////////////////////////////////////////

class DerivedClass : public BaseClass
{
public:

    DerivedClass();

    virtual ~DerivedClass();

    int getOne() override;

//    void operator delete(void*);
};

////////////////////////////////////////////////////////////////////////////////

#endif // DERIVEDCLASS_H_
