#include <iostream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

struct Data
{
    double x;
    double y;
    double z;
    bool v;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    int tab[] = { 10, 20, 30, 40, 50 };

    for ( auto a : tab )
    {
        cout << a << endl;
    }

    cout << endl;

    std::vector< int > v;

    v.push_back( 11 );
    v.push_back( 12 );
    v.push_back( 13 );
    v.push_back( 14 );
    v.push_back( 15 );

    for ( auto a : v )
    {
        cout << a << endl;
    }

    cout << endl;

    for ( auto a : { 21, 22, 23, 24, 25 } )
    {
        cout << a << endl;
    }

    Data data[ 4 ];

    for ( auto &d : data )
    {
        d.v = true;
    }

    for ( auto &d : data )
    {
        cout << (int)d.v << endl;
    }

    return 0;
}
