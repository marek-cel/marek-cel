#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

void funkcja_obslugujaca();

////////////////////////////////////////////////////////////////////////////////

int main()
{
    int *wsk1 = new int;
    int *wsk2 { new int };
    int *wsk3 = new int( 32 );
    int *wsk4 = new int{ 32 };
    int *wsk5 { new int( 32 ) };
    int *wsk6 { new int{ 32 } };

    cout << *wsk1 << endl;
    cout << *wsk2 << endl;
    cout << *wsk3 << endl;
    cout << *wsk4 << endl;
    cout << *wsk5 << endl;
    cout << *wsk6 << endl;

    ///////////////////////////////////

    const int *c_wsk1 = new const int{ 32 };
    const int *c_wsk2 = new const int( 32 );
    //const int *c_wsk3 = new const int; // Error!

    cout << *c_wsk1 << endl;
    cout << *c_wsk2 << endl;

    ///////////////////////////////////

    cout << endl;

    int rozmiar;

    cout << "Podaj rozmiar" << endl;
    cin >> rozmiar;

    int *t_wsk1 = new int[ rozmiar ];
    int *t_wsk2 = new int[ rozmiar ] {};
    int *t_wsk3 = new int[ rozmiar ] { 1 };

    for ( int i = 0; i < rozmiar; i++ )
    {
        cout << t_wsk1[i] << " " << t_wsk2[i] << " " << t_wsk3[i] << endl;
    }

    delete [] t_wsk1;
    delete [] t_wsk2;
    delete [] t_wsk3;

    ///////////////////////////////////

    cout << endl;

    // umiejscawiajacy operator new

    int *osiedle = new int[ 10 ] {};

    void *gdzie = &( osiedle[ 2 ] );

    int *wsk_i = new ( gdzie ) int;

    *wsk_i = 3;

    for ( int i = 0; i < 10; i++ )
    {
        cout << osiedle[ i ] << endl;
    }

    delete [] osiedle; // !!! tylko to !!!

    ///////////////////////////////////

    cout << endl;

    double *wsk_d;

    wsk_d = new ( std::nothrow ) double [ 10000000000000 ];

    if ( !wsk_d )
    {
        cout << "Rezerwacja nieudana." << endl;
    }

    try
    {
        set_new_handler( funkcja_obslugujaca );
        wsk_d = new double [ 10000000000000 ];
    }
    catch ( const std::exception &e )
    {
        cout << "Przechwycony wyjatek: " << e.what() << endl;
    }
    catch ( ... )
    {
        cout << "Przechwycony nieznany wyjatek." << endl;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void funkcja_obslugujaca()
{
    cout << __func__ << endl;
    throw std::bad_alloc();
}
