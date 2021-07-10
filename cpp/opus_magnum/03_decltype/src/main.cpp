#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int fun()
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

int fun( double a )
{
    return static_cast<int>(a);
}

////////////////////////////////////////////////////////////////////////////////

int fun2( double a )
{
    return static_cast<int>(a);
}

////////////////////////////////////////////////////////////////////////////////

template< typename TYPE >
class Klasa
{
public:

    Klasa() {}

    TYPE _a;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    int8_t  i8  = 8;
    int16_t i16 = 16;
    int32_t i32 = 32;

    cout << sizeof( decltype( i8  ) ) << endl;
    cout << sizeof( decltype( i16 ) ) << endl;
    cout << sizeof( decltype( i32 ) ) << endl;

    cout << endl;

    Klasa< decltype( i8  ) > k8;
    Klasa< decltype( i16 ) > k16;
    Klasa< decltype( i32 ) > k32;

    k8  ._a = i8;
    k16 ._a = i16;
    k32 ._a = i32;

    cout << (int)k8  ._a << endl;
    cout << (int)k16 ._a << endl;
    cout << (int)k32 ._a << endl;

    auto pi = 3.14;
    decltype(pi) pi_2 = pi / 2.0;

    cout << pi << endl;
    cout << pi_2 << endl;

    //using Twfun = decltype(fun); // error!
    using Twfun = int(*)(double);
    Twfun pfun = &fun;

    int a = pfun( 3.14 );

    cout << a << endl;

    using Twfun2 = decltype(fun2);
    Twfun pfun2 = &fun2;

    int b = pfun2( 3.14 );

    cout << b << endl;

    return 0;
}
