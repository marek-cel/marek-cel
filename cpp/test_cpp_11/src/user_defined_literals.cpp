#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class Velocity
{
public:

    Velocity() = default;

    constexpr Velocity( double vel ) :
        _vel ( vel )
    {}

    double getVel() const { return _vel; }

private:

    double _vel {};
};

////////////////////////////////////////////////////////////////////////////////

constexpr Velocity operator"" _mps( long double vel )
{
    return Velocity( vel );
}

////////////////////////////////////////////////////////////////////////////////

constexpr Velocity operator"" _kmh( long double vel )
{
    return Velocity(  vel / 3.6 );
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    Velocity v1 = 10.1_mps;
    Velocity v2 = 10.1_kmh;
    //Velocity v3 = 10.1_KMH; // error!

    cout << v1.getVel() << endl;
    cout << v2.getVel() << endl;

    return 0;
}
