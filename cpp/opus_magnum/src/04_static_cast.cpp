#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class Pojazd
{
public:

    Pojazd() { _nazwa = ""; }

    string _nazwa;
};

////////////////////////////////////////////////////////////////////////////////

class Samochod : public Pojazd
{
public:

    Samochod( int moc ) { _nazwa = "Samochod"; _moc = moc; }

    int _moc;
};

////////////////////////////////////////////////////////////////////////////////

class Rower : public Pojazd
{
public:

    Rower() { _nazwa = "Rower"; }
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    Pojazd *p1 = new Samochod( 100 );
    Pojazd *p2 = new Rower();


    Samochod *s1 = static_cast< Samochod* >( p1 );
    Samochod *s2 = static_cast< Samochod* >( p2 );

    if ( s1 ) cout << s1->_nazwa << " " << s1->_moc << endl;
    if ( s2 ) cout << s2->_nazwa << " " << s2->_moc << endl;

    //////////////////////////////

    double v1 = 1.0;

    double *pv1 = &v1;
    void *pp = pv1;

    double *pd1 = static_cast< double* >( pp );
    int    *pi1 = static_cast< int*    >( pp );

    if ( pd1 ) cout << "pd1= " << (*pd1) << endl;
    if ( pi1 ) cout << "pi1= " << (*pi1) << endl;

    //////////////////////////////

    return 0;
}
