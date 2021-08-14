#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

#define AAA 20
#define BBB 30
#define CCC AAA + BBB

constexpr int trzy = 3;
#define DZIESIEC 10;

////////////////////////////////////////////////////////////////////////////////

void f()
{
    double s1 = trzy / DZIESIEC;
    double s2 = DZIESIEC + trzy;
    //double s3 = DZIESIEC / trzy; // Error!!!
}

////////////////////////////////////////////////////////////////////////////////

#define DELPTR( ptr ) \
{ \
    if ( ptr ) delete ptr; \
    ptr = nullptr; \
}

////////////////////////////////////////////////////////////////////////////////

#define SP( co, jaki ) co ## jaki

#define WYPISZ( arg ) cout << #arg << "=" << arg << endl;

#define DZIEL( a, b ) (a/b)

////////////////////////////////////////////////////////////////////////////////

class Klasa
{
public:

    static void fun()
    {
        cout << __func__ << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "(2*CCC)= " << (2*CCC) << endl;

    cout << "DZIEL(2+3,5.0)= " << DZIEL(2+3,5.0) << endl;

    int SP( statecznik, Poziomy );

    statecznikPoziomy = 1;

    WYPISZ( statecznikPoziomy );

#   if NAZWA == NAZWA2
    // ..
#   endif

#   if NAZWA > 2
    // ..
#   endif

#   if ( NAZWA_A == 2 || NAZWA_B > 10 )
    // ..
#   endif

#   if ( NAZWA == 6 && defined(WERSJA_ROBOCZA) )
    // ..
#   endif

#   line 999
#   warning AAA

    // __cplusplus__
    // C++ 1998/2003 : 199711L
    // C++ 2011      : 201103L

    Klasa::fun();

    return 0;
}
