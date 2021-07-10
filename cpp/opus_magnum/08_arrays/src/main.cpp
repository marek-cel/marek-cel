#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

int glob_tab[40];

////////////////////////////////////////////////////////////////////////////////

int main()
{
    int aaa[3] {}; // inicjalizuje tablice zerami
    int bbb[3];

    for ( int i = 0; i < 3; i++ )
    {
        cout << "aaa= " << aaa[i] << " bbb= " << bbb[i] << endl;
    }

    /////////////////////////////////

    double loc_tab[40];

    cout << "glob_tab[2]= " << glob_tab[2] << endl;
    cout << "loc_tab[2]= " << loc_tab[2] << endl;

    /////////////////////////////////

    int tab[10] { 1, 2, 3, 4 };

    for ( int i = 0; i < 10; i++ )
    {
        cout << "tab= " << tab[i] << endl;
    }

    /////////////////////////////////

    char str[10] = { "ABCD" };

    cout << str << endl;


    /////////////////////////////////

    int rozmiar = 10;
    cout << "Podaj rozmiar ";
    cin >> rozmiar;

    int tabl[ rozmiar ] {};

    for ( int i = 0; i < rozmiar; i++ )
    {
        cout << "tabl= " << tabl[i] << endl;
    }


    return 0;
}
