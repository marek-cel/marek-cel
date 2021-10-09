#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class A
{
public:

    A() {}

    virtual void foo()
    {
        cout << "A::foo()" << endl;
    }

    virtual void bar()
    {
        cout << "A::bar()" << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////

class B : public A
{
public:

    B() {}

    virtual void foo() override
    {
        cout << "B::foo()" << endl;
    }

    virtual void bar() override;

    //virtual void fun() override // error!
    virtual void fun()
    {
        cout << "B::fun()" << endl;
    }
};

//void B::bar() override // error!
//virtual void B::bar() // error!
void B::bar()
{
    cout << "B::bar()" << endl;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    B b;
    b.foo();
    b.bar();
    b.fun();

    return 0;
}
