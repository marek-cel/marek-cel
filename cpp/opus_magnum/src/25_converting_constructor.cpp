#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class Complex
{
public:

    Complex( double re )
    {
        _re = re;
    }

    Complex( double re, double im )
    {
        _re = re;
        _im = im;
    }

    double _re { 0.0 };
    double _im { 0.0 };
};

////////////////////////////////////////////////////////////////////////////////

class A
{
public:

    A() {}

    explicit A( int a ) {}
};

////////////////////////////////////////////////////////////////////////////////

Complex add( Complex a, Complex b )
{
    return Complex( a._re + b._re, a._im + b._im );
}

////////////////////////////////////////////////////////////////////////////////

void fun( A a )
{
    cout << __func__ << endl;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    ////////////////////////////////////////

    Complex c1( 1.0, 2.0 );
    Complex c2( 1.0, 2.0 );

    Complex c3 = add( c1, c2 );
    Complex c4 = add( c1, 1.0 );
    Complex c5 = add( 1.0, c2 );

    cout << c3._re << " " << c3._im << endl;
    cout << c4._re << " " << c4._im << endl;
    cout << c5._re << " " << c5._im << endl;

    ////////////////////////////////////////

    A a1;

    fun( a1 );
    //fun( 77 ); // error!

    ////////////////////////////////////////

    return 0;
}
