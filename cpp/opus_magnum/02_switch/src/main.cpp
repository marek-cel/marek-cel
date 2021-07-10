#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

constexpr int aaa()
{
    return 1;
}

////////////////////////////////////////////////////////////////////////////////

int zzz( int a )
{
    return a;
}

////////////////////////////////////////////////////////////////////////////////

void fun( int var )
{
    constexpr int bbb = 2;
    const int ccc = 3;
    int xxx = 3;
    const int yyy = zzz( var );

    //bbb = 999; // ERROR!
    //ccc = 999; // ERROR!
    //yyy = 999; // ERROR!

    switch ( var )
    {
    case 0:
        cout << "0" << endl;
        break;

    case aaa():
        cout << "aaa()" << endl;
        break;

    case bbb:
        cout << "bbb" << endl;
        break;

    case ccc:
        cout << "ccc" << endl;
        break;

//    case xxx:                  // ERROR!
//        cout << "xxx" << endl; // ERROR!
//        break;                 // ERROR!

//    case yyy:                  // ERROR!
//        cout << "yyy" << endl; // ERROR!
//        break;                 // ERROR!

    default:
        cout << "default" << endl;
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    fun( 0 );
    fun( 1 );
    fun( 2 );
    fun( 3 );

    fun( -1 );

    return 0;
}
