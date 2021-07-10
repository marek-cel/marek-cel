#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class A
{
public:

    A() {}

    virtual void fun()
    {
        cout << "A::fun()" << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////

class B : public A
{
public:

    B() {}

    virtual void fun() override
    {
        cout << "B::fun()" << endl;
    }

    //virtual void fun( int a ) override // error!
    virtual void fun( int a )
    {
        cout << "B::fun(int) " << a << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    B b;
    b.fun();
    b.fun( 1 );

    return 0;
}
