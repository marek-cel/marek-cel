#include <iostream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int count( const vector< int > &vect, bool (*fun)(int) )
{
    int n = 0;

    for ( auto v : vect )
    {
        if ( fun )
        {
            if ( fun( v ) )
            {
                n++;
            }
        }
    }

    return n;
}

////////////////////////////////////////////////////////////////////////////////

bool is_even( int a )
{
    return ( a % 2 ) == 0;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    vector<int> vect { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    int n1 = count( vect, nullptr );
    int n2 = count( vect, is_even );

    cout << n1 << endl;
    cout << n2 << endl;

    return 0;
}
