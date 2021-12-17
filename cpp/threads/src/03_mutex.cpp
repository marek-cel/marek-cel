#include <iostream>
#include <mutex>
#include <thread>

#ifdef WIN32
#   include <windows.h>
#else
#   include <unistd.h>
#endif

////////////////////////////////////////////////////////////////////////////////

int g_var = 0;
std::mutex g_var_mutex;

////////////////////////////////////////////////////////////////////////////////

void fun1( const char *msg, int delay )
{
    for (;;)
    {
        std::cout << msg << " time= " << time( nullptr ) << std::endl;

        {
            // lock_guard is a mutex wrapper that provides a convenient RAII-style
            // mechanism for owning a mutex for the duration of a scoped block
            std::lock_guard<std::mutex> lock( g_var_mutex );
            ++g_var;

            std::cout << msg << " g_var= " << g_var << std::endl;

            // g_var_mutex is automatically released when lock goes out of scope
        }

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

    // waits for the thread to finish its execution
    t1.join();
    t2.join();

    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;

    return 0;
}
