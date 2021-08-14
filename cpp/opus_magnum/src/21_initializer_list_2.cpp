#include <iostream>
#include <initializer_list>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

class Pomiary
{
public:

    Pomiary( initializer_list<int> list )
    {
        cout << "Pomiary( initializer_list<int> list )" << endl;
        for ( auto x : list ) _dane.push_back( x );
    }

    Pomiary( int x1, int x2 )
    {
        cout << "Pomiary( int x1, int x2 )" << endl;
        _dane.push_back( x1 );
        _dane.push_back( x2 );
    }

    void wypisz()
    {
        for ( auto x : _dane ) { cout << x << " "; } cout << endl;
    }

private:

    vector< int > _dane;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    //////////////////////////////////////////

    vector<int> v1( { 1, 2, 3 } );
    vector<int> v2  { 1, 2, 3 };

    for ( auto v : v1 ) { cout << v << " "; } cout << endl;
    for ( auto v : v2 ) { cout << v << " "; } cout << endl;

    //////////////////////////////////////////

    Pomiary p1{ 11, 22 };
    Pomiary p2 = { 11, 22 };
    Pomiary p3( { 11, 22 } );
    Pomiary p4( 11, 22 );

    p1.wypisz();
    p2.wypisz();
    p3.wypisz();
    p4.wypisz();

    //////////////////////////////////////////

    return 0;
}
