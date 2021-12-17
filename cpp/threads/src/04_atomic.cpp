#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    std::atomic<int> count( 0 );

    const int ITERATIONS = 1e6;

    auto func = [&count]()
    {
        for ( int i = 0; i < ITERATIONS; i++ )
        {
            ++count;
        }
    };

    // constructs new thread objects
    std::thread t1( func );
    std::thread t2( func );

    t1.join();
    t2.join();

    std::cout << count << std::endl;

    return 0;
}
