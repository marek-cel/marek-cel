#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

auto fun( int a, int b ) -> decltype( a + b )
{
    return a + b;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << fun( 1, 2 ) << endl;

    {
        auto fun( int a = 2, int b = 2 ) -> decltype( a + b );

        cout << fun( 1 ) << endl;
        cout << fun() << endl;

        {
            auto fun( int a, int b = 9 ) -> decltype( a + b );
            cout << fun( 1 ) << endl;
        }
    }

    return 0;
}
