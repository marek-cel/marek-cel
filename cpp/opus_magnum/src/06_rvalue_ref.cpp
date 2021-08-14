#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

int fun1( int &rval_ref )
{
    rval_ref = 1;

    return rval_ref;
}

int fun2( const int &rval_ref )
{
    //rval_ref = 2;

    return rval_ref;
}

int fun3( int &&rval_ref )
{
    rval_ref = 3;

    return rval_ref;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    //int a = fun1( 2 ); // ERROR!
    int b = fun2( 4 );
    cout << "b= " << b << endl;

    int b2 = fun2( 4 + 1 );
    int b3 = fun2( b + 1 );
    int c = fun3( 2 );
    //int d = fun3( b ); // ERROR!
    int d = fun3( std::move( b ) );
    int e = fun3( b + 2 );

    cout << "XxXxXxXxXxXx" << endl;

    //cout << "a= " << a << endl;
    cout << "b= " << b << endl;
    cout << "b2= " << b2 << endl;
    cout << "b3= " << b3 << endl;
    cout << "c= " << c << endl;
    cout << "d= " << d << endl;
    cout << "e= " << e << endl;

    return 0;
}
