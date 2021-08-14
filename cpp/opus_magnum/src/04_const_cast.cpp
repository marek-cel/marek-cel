#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

void fun( int *x )
{
    (*x) = 111;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    const int a = 999;

    cout << a << endl;

    cout << endl;

    //fun( &a ); // ERROR!
    int *a_ptr = const_cast<int*>(&a);
    fun( a_ptr );

    cout << a << endl;
    cout << (*a_ptr) << endl;

    cout << endl;

    cout << (&a) << endl;
    cout << a_ptr << endl;

    cout << endl;

    (*a_ptr) = 888;

    cout << a << endl;
    cout << (*a_ptr) << endl;

    cout << endl;

    return 0;
}
