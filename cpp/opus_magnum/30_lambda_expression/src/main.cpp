#include <algorithm>
#include <iostream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class IsLessThan
{
public:

    IsLessThan( int v ) : _v( v ) {}

    bool operator ()( int i )
    {
        return i < _v;
    }

private:

    int _v {};
};

////////////////////////////////////////////////////////////////////////////////

int count( const vector< int > &vect, bool (*fun)(int) )
{
    int n = 0;
    for ( auto v : vect )
    {
        if ( fun )
        {
            if ( fun( v ) ) n++;
        }
    }
    return n;
}

////////////////////////////////////////////////////////////////////////////////

int count( const vector< int > &vect, IsLessThan ilt )
{
    int n = 0;
    for ( auto v : vect )
    {
        if ( ilt( v ) ) n++;
    }
    return n;
}

////////////////////////////////////////////////////////////////////////////////

int count2( const vector< int > &vect, function< bool(int) > fun = [](int){return true;} )
{
    int n = 0;
    for ( auto v : vect )
    {
        if ( fun )
        {
            if ( fun( v ) ) n++;
        }
    }
    return n;
}

////////////////////////////////////////////////////////////////////////////////

bool is_odd( int a )
{
    return a % 2;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    ////////////////////////////////////////

    vector<int> vect { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    IsLessThan ilt3( 3 );
    IsLessThan ilt4( 4 );

    ////////////////////////////////////////

    int c0 = count( vect, nullptr );
    cout << c0 << endl;

    int c1 = count( vect, is_odd );
    int c2 = count( vect, ilt3 );
    int c3 = count( vect, ilt4 );

    cout << endl;
    cout << c1 << endl;
    cout << c2 << endl;
    cout << c3 << endl;

    ////////////////////////////////////////

    int k1 = count_if( vect.begin(), vect.end(), is_odd );
    int k2 = count_if( vect.begin(), vect.end(), ilt3 );
    int k3 = count_if( vect.begin(), vect.end(), ilt4 );

    cout << endl;
    cout << k1 << endl;
    cout << k2 << endl;
    cout << k3 << endl;

    ////////////////////////////////////////

    int l1 = count_if( vect.begin(), vect.end(), [](int a){ return a % 2; } );
    int l2 = count_if( vect.begin(), vect.end(), [](int a){ return a < 3; } );
    int l3 = count_if( vect.begin(), vect.end(), [](int a){ return a < 4; } );

    cout << endl;
    cout << l1 << endl;
    cout << l2 << endl;
    cout << l3 << endl;

    []( const char *text ){ cout << "Lambda przysłało mi " << text << endl; }( "argo" );

    int p1 = 2;
    int p2 = 3;
    int p3 = 4;

    int m1 = count_if( vect.begin(), vect.end(), [p1](int a){ return a % p1; } );
    int m2 = count_if( vect.begin(), vect.end(), [p2](int a){ return a < p2; } );
    int m3 = count_if( vect.begin(), vect.end(), [p3](int a){ return a < p3; } );

    cout << endl;
    cout << m1 << endl;
    cout << m2 << endl;
    cout << m3 << endl;

    int n1 = count_if( vect.begin(), vect.end(), [](int a) noexcept -> bool { return a % 2; } );
    int n2 = count_if( vect.begin(), vect.end(), [](int a){ return a < 3; } );

    cout << endl;
    cout << n1 << endl;
    cout << n2 << endl;

    [] { cout << "Lambda bez argumentów" << endl; }();

    int o1 = count_if( vect.begin(), vect.end(), [=](int a){ return a % p1; } );
    int o2 = count_if( vect.begin(), vect.end(), [&](int a){ return a < p2; } );
    int o3 = count_if( vect.begin(), vect.end(), [=,&p3](int a){ return a < p3; } );

    cout << endl;
    cout << o1 << endl;
    cout << o2 << endl;
    cout << o3 << endl;

    ////////////////////////////////////////

    int z0 = count2( vect, nullptr );

    cout << endl;
    cout << z0 << endl;

    int z1 = count2( vect, is_odd );
    int z2 = count2( vect, ilt3 );
    int z3 = count2( vect, [](int a){ return a < 4; } );

    cout << endl;
    cout << z1 << endl;
    cout << z2 << endl;
    cout << z3 << endl;

    int z4 = count2( vect );

    cout << endl;
    cout << z4 << endl;

    ////////////////////////////////////////

    return 0;
}
