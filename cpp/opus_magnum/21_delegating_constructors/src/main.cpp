#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class A
{
public:

    A() :
        A( 0, 0 )
    {}

    A( int a ) :
        A( a, 777 )
    {}

    A( int a, int b )
    {
        _a = a;
        _b = b;
    }

    int getA() { return _a; }
    int getB() { return _b; }

private:

    int _a, _b;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    A a( 1 );

    cout << a.getA() << " " << a.getB() << endl;

    return 0;
}
