#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class Klasa
{
public:

    Klasa() {}

    void fun() const
    {
        b = 3;
    }

    void fun2()
    {
        a = 2;
        b = 3;
    }

    int a { 1 };
    mutable int b { 2 };
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    const Klasa k;

    cout << k.a << " " << k.b << endl;

    k.fun();

    cout << k.a << " " << k.b << endl;

    //k.fun2(); // error!

    return 0;
}
