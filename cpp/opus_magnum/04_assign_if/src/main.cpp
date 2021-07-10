#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    int a = 0;
    int b = 1;

    if ( a = b ) // warning
    {
        cout << "a= " << a << endl;
    }

    int c = 0;
    int d = 1;

    if ( ( c = d ) ) // no warning
    {
        cout << "c= " << c << endl;
    }


    return 0;
}
