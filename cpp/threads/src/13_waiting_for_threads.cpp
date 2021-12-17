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

    std::atomic<bool> ready( false );

    // constructs new thread object
    std::thread t1( [&]()
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
        ready = true;
    });

    while ( !ready )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    }

    std::cout << "ready " << ready << std::endl;

    t1.join();

    return 0;
}
