#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class A
{
public:

    A( int size )
    {
        _size = size;
        _tab = new int[ _size ];
    }

    ~A()
    {
        if ( _tab ) delete [] _tab;
        _tab = nullptr;
    }

    A& operator=( A &&a )
    {
        cout << "A::operator=(A&&)" << endl;

        _size = a._size;
        _tab  = a._tab;

        a._size = 0;
        a._tab = nullptr;

        return (*this);
    }

    int _size {};
    int *_tab {};
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    A a1( 7 );
    A a2( 3 );

    a1 = std::move( a2 );

    return 0;
}
