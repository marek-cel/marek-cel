#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

////////////////////////////////////////////////////////////////////////////////

void fun( int &count, std::mutex &mtx )
{
    for ( int i = 0; i < 1e6; i++ )
    {
        mtx.lock();
        ++count;
        mtx.unlock();
    }
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    int count = 0;

    std::mutex mtx;

    // constructs new thread objects
    std::thread t1( fun, std::ref(count), std::ref(mtx) );
    std::thread t2( fun, std::ref(count), std::ref(mtx) );

    t1.join();
    t2.join();

    std::cout << count << std::endl;

    return 0;
}
