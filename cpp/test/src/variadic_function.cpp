#include <iostream>
#include <cstdarg>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

// valid, but the arguments cannot be accessed portably
//void varFun( ... )
//{
//    cout << "varFun( ... )" << endl;
//}

////////////////////////////////////////////////////////////////////////////////

void varFun( int len, ... )
{
    // Within the body of a function that uses variadic arguments, the values of
    // these arguments may be accessed using the <cstdarg> library facilities:

    cout << "len= " << len << endl;

    va_list args;

    // args - an instance of the va_list type
    // len  - the named parameter preceding the first variable parameter
    va_start( args, len );

    for ( int i = 0; i < len; i++ )
    {
        cout << va_arg( args, double ) << endl;
    }

    va_end( args );
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << __cplusplus << endl;

    varFun( 3, 1.1, 2.2, 3.14 );

    return 0;
}
