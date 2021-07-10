#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class A
{
public:

    A() {}

    A( int x, int y, int z )
    {
        _x = x;
        _y = y;
        _x = z;
    }

    void fun() { cout << __func__ << endl; }

    int _x { 1 };
    int _y { 2 };
    int _z { 3 };
};

////////////////////////////////////////////////////////////////////////////////

class B : public    A {};
class C : protected A {};
class D : private   A {};

////////////////////////////////////////////////////////////////////////////////

class E : private A
{
public:

    using A::_x;
};

////////////////////////////////////////////////////////////////////////////////

class F : public A
{
public:

    using A::A;

private:

    using A::_x;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    A a;
    B b;
    C c;
    D d;

    a.fun();
    b.fun();
    //c.fun(); // error!
    //d.fun(); // error!

    E e;
    F f( 7, 8, 9 );

    cout << e._x << endl;

    //cout << f._x << endl; // error!
    cout << f._y << endl;

    return 0;
}
