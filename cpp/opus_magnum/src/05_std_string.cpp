#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    string str1 = "lorem";

    if ( str1 == "lorem" )
    {
        cout << "takie same >>lorem<<" << endl;
    }

    if ( str1 == "LOREM" )
    {
        cout << "takie same >>LOREM<<" << endl;
    }

    //////////////////////////

    string str2 = "";

    str2 = to_string( 3.14 );

    cout << str2 << endl;

    return 0;
}
