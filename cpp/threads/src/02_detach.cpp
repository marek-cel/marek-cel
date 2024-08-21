#include <iostream>
#include <thread>
#include <chrono>

#ifdef WIN32
#   include <windows.h>
#else
#   include <unistd.h>
#endif

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
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    // constructs new thread objects
    std::thread t1( fun1, "t1", 1000 );
    std::thread t2( fun1, "t2", 1500 );

    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;

    // permits the thread to execute independently from the thread handle
    t1.detach();
    t2.detach();

    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
    std::chrono::seconds delay(10);
    std::this_thread::sleep_for(delay);
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;

    return 0;
}
