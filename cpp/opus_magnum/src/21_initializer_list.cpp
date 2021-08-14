#include <iostream>
#include <initializer_list>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

double suma( std::initializer_list<double> lista );

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    //////////////////////////////////////

    int x { 7 };
    cout << x << endl;

    int tab[5] { 1,2,3,4,5 };
    for ( int t : tab ) cout << t << " ";
    cout << endl;

    //////////////////////////////////////

    initializer_list<int> ilist { 11,22,33,44,55 };

    for ( int i : ilist ) cout << i << " ";
    cout << endl;

    const int *iwsk = ilist.begin();
    while ( iwsk != ilist.end() )
    {
        cout << *iwsk << " ";
        ++iwsk;
    }
    cout << endl;

    for ( size_t i = 0; i < ilist.size(); i++ )
    {
        cout << ilist.begin()[ i ] << " ";
    }
    cout << endl;

    //////////////////////////////////////

    // auto alist = { 3.14, 4, 5, 6 }; // error!
    auto alist = { 3.14, 4.0, 5.0, 6.0 };
    for ( auto a : alist ) cout << a << " ";
    cout << endl;

    const auto *awsk = alist.begin();

    while ( awsk != alist.end() )
    {
        cout << *awsk << " ";
        ++awsk;
    }
    cout << endl;

    //////////////////////////////////////

    for ( auto x : { 3.14, 1.1, 2.2 } )
    {
        cout << x << " ";
    }
    cout << endl;

    //////////////////////////////////////

    cout << suma( {} ) << endl;
    cout << suma( { 1.1, 2.2 } ) << endl;

    //////////////////////////////////////

    int a1 = 1;
    int a2 = 2;
    initializer_list<int> ilist2 { 0, a1, a2, 3, a2 };

    for ( int i : ilist2 ) cout << i << " ";
    cout << endl;

    //////////////////////////////////////

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

double suma( std::initializer_list<double> lista )
{
    double result = 0.0;

    for ( auto x : lista )
    {
        result += x;
    }

    return result;
}
