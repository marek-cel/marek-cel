#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class Filtr
{
public:

    Filtr( char l, char u ) :
        _l ( l ), _u ( u )
    {}

    char operator ()( char c )
    {
        if ( c > _l && c < _u ) return c;

        return '.';
    }

private:

    char _l;
    char _u;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    char s[] = { "lorem ipsum" };

    Filtr f( 'f', 'n' );

    for ( auto c : s )
    {
        cout << f( c );
    }

    cout << endl;

    return 0;
}
