#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

void fun( const char *str );
void fun2();

////////////////////////////////////////////////////////////////////////////////

int main()
{
    //fun( __func__ ); // error !
    fun2();

    return 0;
}