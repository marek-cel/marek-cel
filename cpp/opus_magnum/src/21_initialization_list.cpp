#include <iostream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

vector< int > gv;

////////////////////////////////////////////////////////////////////////////////

class A
{
public:

    const int _a;
    int _b;

    A( int a, int b ) :
        _a { a },
        _b { b }
    {
        _b = 999;
    }
};

////////////////////////////////////////////////////////////////////////////////

class B
{
public:

    const int _x;

    B() try :
        _x { gv.at( 2 ) }
    {
        // constructor body
    }
    catch ( const exception &e )
    {
        cout << "Exception caught: " << e.what() << endl;
    }
    catch ( ... )
    {
        cout << "Unknown exception" << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    gv.push_back( 1 );

    A a( 1, 2 );
    cout << a._a << " " << a._b << endl;

    B b;
    cout << b._x << endl;

    return 0;
}
