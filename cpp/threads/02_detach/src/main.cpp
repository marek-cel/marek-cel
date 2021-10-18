#include <iostream>
#include <thread>

#ifdef WIN32
#   include <windows.h>
#else
#   include <unistd.h>
#endif

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

void fun1( const char *msg, int delay )
{
    for (;;)
    {
        std::cout << msg << " " << time( nullptr ) << std::endl;

#       ifdef WIN32
        Sleep( delay );
#       else
        usleep( 1000 * delay );
#       endif
    }
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << __cplusplus << endl;

    // constructs new thread object
    std::thread t1( fun1, "t1", 1000 );
    std::thread t2( fun1, "t2", 1500 );

    cout << __FILE__ << "(" << __LINE__ << ")" << endl;

    // permits the thread to execute independently from the thread handle
    t1.detach();
    t2.detach();

    cout << __FILE__ << "(" << __LINE__ << ")" << endl;

    return 0;
}
