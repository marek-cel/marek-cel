#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

static void fun( const char *str )
{
    cout << str << endl;
}

////////////////////////////////////////////////////////////////////////////////

void fun2()
{
    fun( __func__ );
}