#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

////////////////////////////////////////////////////////////////////////////////

void fun( int &count, std::mutex &mtx )
{
    for ( int i = 0; i < 1e6; i++ )
    {
        std::lock_guard<std::mutex> guard(mtx);
        ++count;
        // lock guard is out of scope and unlocks mutex
        // this can also be done with std::unique_lock
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
