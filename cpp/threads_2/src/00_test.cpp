#include <chrono>
#include <iostream>
#include <thread>

#ifdef WIN32
#   include <windows.h>
#else
#   include <unistd.h>
#endif

////////////////////////////////////////////////////////////////////////////////

void fun()
{
    for ( int i = 0; i < 10; ++i )
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "Loop " << i << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    std::thread t1(fun);
    std::thread t2(fun);

    t1.join();
    t2.join();

    return 0;
}
