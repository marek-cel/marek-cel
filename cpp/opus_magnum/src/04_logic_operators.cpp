#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    bool a = true;
    bool b = false;

    ///////////////////////////////////

    if ( a && b )
    {
        cout << "a i b" << endl;
    }
    else
    {
        cout << "nie a i b" << endl;
    }

    if ( a and b )
    {
        cout << "a i b" << endl;
    }
    else
    {
        cout << "nie a i b" << endl;
    }

    ///////////////////////////////////

    if ( a || b )
    {
        cout << "a lub b" << endl;
    }
    else
    {
        cout << "nie a lub b" << endl;
    }

    if ( a or b )
    {
        cout << "a lub b" << endl;
    }
    else
    {
        cout << "nie a lub b" << endl;
    }

    ///////////////////////////////////

    if ( !( a || b ) )
    {
        cout << "nie a lub b" << endl;
    }
    else
    {
        cout << "a lub b" << endl;
    }

    if ( not( a or b ) )
    {
        cout << "nie a lub b" << endl;
    }
    else
    {
        cout << "a lub b" << endl;
    }

    ///////////////////////////////////

    return 0;
}
