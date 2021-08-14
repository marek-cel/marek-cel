#include <iomanip>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    int a = 1'000'001;
    double x = 2'000'001.361'423;

    cout.setf( ios_base::showpoint );
    cout.setf( ios_base::fixed );

    cout << setprecision( 6 );

    cout << a << endl;
    cout << x << endl;

    return 0;
}
