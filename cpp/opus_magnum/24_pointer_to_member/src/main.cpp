#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class A
{
public:

    A() { _x = 7; }

    void fun()
    {
        cout << __func__ << endl;
    }

    int _x;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    ////////////////////////////////////

    A a;
    A *aptr = &a;

    ////////////////////////////////////

    int *iptr = &a._x;

    cout << *iptr << endl;

    ////////////////////////////////////

    int A::*mptr = &A::_x;

    cout << (a.*mptr) << endl;
    cout << (aptr->*mptr) << endl;

    ////////////////////////////////////

    //void (*fptr)() = &A::fun; // error!
    void (A::*fptr)() = &A::fun;

    (a.*fptr)();
    (aptr->*fptr)();

    ////////////////////////////////////

    using VarPtr = decltype( &A::_x );
    VarPtr mptr2 = &A::_x;

    cout << (a.*mptr2) << endl;
    cout << (aptr->*mptr2) << endl;

    ////////////////////////////////////

    using FunPtr = decltype( &A::fun );
    FunPtr fptr2 = &A::fun;

    (a.*fptr2)();
    (aptr->*fptr2)();

    ////////////////////////////////////

    auto mptr3 = &A::_x;

    cout << (a.*mptr3) << endl;
    cout << (aptr->*mptr3) << endl;

    ////////////////////////////////////

    auto fptr3 = &A::fun;

    (a.*fptr3)();
    (aptr->*fptr3)();

    ////////////////////////////////////

    return 0;
}
