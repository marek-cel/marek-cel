#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

struct A
{
    int a;
    int b;
    double x;
    double y;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    A a { 3, 2, 3.14, 2.71 };

    cout << a.a << " ";
    cout << a.b << " ";
    cout << a.x << " ";
    cout << a.y << endl;

    A tab[2] { { 1, 2, 1.1, 2.2 }, { 10, 20, 11.1, 22.2 } };

    for ( auto a  : tab )
    {
        cout << a.a << " ";
        cout << a.b << " ";
        cout << a.x << " ";
        cout << a.y << endl;
    }

    return 0;
}
