#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    double v1 = 1.0;

    double *pv1 = &v1;
    void *pp = pv1;

    double *pd1 = reinterpret_cast< double* >( pp );
    int    *pi1 = reinterpret_cast< int*    >( pp );

    if ( pd1 ) cout << "pd1= " << (*pd1) << endl;
    if ( pi1 ) cout << "pi1= " << (*pi1) << endl;

    return 0;
}
