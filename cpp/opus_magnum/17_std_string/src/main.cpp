#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::string str;

    str += "aaaaaa";

    for ( int i = 0; i < 10; i++ )
    {
        str += to_string( i );

        cout << str << endl;
        cout << str.capacity() << endl;
        cout << endl;
    }

    str.shrink_to_fit(); // C++11
    cout << str << endl;
    cout << str.capacity() << endl;
    cout << endl;

    str.resize( 10 );
    cout << str << endl;

    str.resize( 12, 'x' );
    cout << str << endl;

    cout << str.front() << " " << str.back() << endl;

    str.erase( 10, 2 );
    cout << str << endl;

    str.pop_back();
    cout << str << endl;

    str.insert( 2, "bbb" );
    cout << str << endl;

    str.insert( 2, 2, 'c' );
    cout << str << endl;

    str.replace( 2, 2, 2, '_' );
    cout << str << endl;

    string str2;

    cout << u8"Wpisz coś na ekran" << endl;

    cin >> std::ws;
    getline( cin, str2 );

    cout << str2 << endl;

    return 0;
}
