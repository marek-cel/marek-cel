#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class A
{
public:

    A() = default;

    A( int size )
    {
        cout << "A::A(int)" << endl;

        _size = size;
        _tab = new int[ _size ];

        for ( int i = 0; i < _size; i++ )
        {
            _tab[ i ] = i;
        }
    }

    A( A &&a )
    {
        cout << "A::A(A&&)" << endl;

        _size = a._size;
        _tab = a._tab;

        a._size = 0;
        a._tab = nullptr;
    }

    ~A()
    {
        if ( _tab ) delete [] _tab;
        _tab = nullptr;
    }

    int _size { 0 };
    int *_tab { nullptr };
};

////////////////////////////////////////////////////////////////////////////////

A fun( int i )
{
    A a1( 1 );
    A a2( 2 );
    A a3( 3 );

    if ( i == 1 ) return a1;
    if ( i == 2 ) return a2;

    return a3;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    A a = fun( 3 );

    for ( int i = 0; i < a._size; i++ )
    {
        cout << a._tab[ i ] << endl;
    }

    return 0;
}
