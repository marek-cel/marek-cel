#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class Kolor
{
public:

    constexpr Kolor() :
        Kolor( 0, 0, 0 )
    {}

    constexpr Kolor( unsigned char r, unsigned char g, unsigned char b ) :
        _r ( r ), _g( g ), _b( b )
    {}

    int r() const { return _r; }
    int g() const { return _g; }
    int b() const { return _b; }

private:

    unsigned char _r,_g,_b;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    constexpr Kolor gree( 0, 255, 0 );

    Kolor blue( 0, 0, 255 );

    cout << gree.r() << " " << gree.g() << " " << gree.b() << endl;
    cout << blue.r() << " " << blue.g() << " " << blue.b() << endl;

    return 0;
}
