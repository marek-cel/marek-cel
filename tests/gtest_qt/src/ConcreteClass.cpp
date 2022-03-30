#include <ConcreteClass.h>

////////////////////////////////////////////////////////////////////////////////

ConcreteClass::ConcreteClass() :
    AbstractClass()
{
    constexpr int size = 10;

    _bar = new int[ size ];

    for ( int i = 0; i < size; ++i )
    {
        _bar[i] = i+1;
    }
}

////////////////////////////////////////////////////////////////////////////////

ConcreteClass::~ConcreteClass()
{
    if ( _bar ) delete [] _bar;
}

////////////////////////////////////////////////////////////////////////////////

int ConcreteClass::getOne()
{
    return AbstractClass::getOne();
}
