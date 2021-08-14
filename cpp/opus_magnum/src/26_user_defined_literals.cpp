#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class Temperatura
{
public:

    constexpr Temperatura( double deg_c ) :
        _deg_c ( deg_c )
    {}

    double _deg_c;
};

constexpr Temperatura operator"" _degC( long double temp )
{
    return Temperatura( temp );
}

constexpr Temperatura operator"" _degF( long double temp )
{
    return Temperatura( 5.0 * ( temp - 32.0 ) / 9.0 );
}

int operator"" _s( const char *text, size_t len )
{
    cout << text << endl;
    return len;
}

int operator"" _bin( const char *text )
{
    for ( const char *ptr = text; *ptr != '\0'; ptr++ )
    {
        cout << *ptr << " ";
    }
    cout << endl;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    constexpr Temperatura t1 = 15.0_degC;
    constexpr Temperatura t2 = 100.0_degF;

    cout << t1._deg_c << endl;
    cout << t2._deg_c << endl;

    Temperatura t3( 100.0 );
    t3._deg_c = 0.0;

    cout << t3._deg_c << endl;

    int a = "jakis_tekst"_s;
    cout << a << endl;

    int b = 11011011_bin;
    cout << b << endl;

    return 0;
}
