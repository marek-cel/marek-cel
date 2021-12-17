#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    std::condition_variable condition;
    std::mutex mtx;
    bool ready = false;

    // constructs new thread object
    std::thread t1( [&]()
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
        std::unique_lock<std::mutex> lock( mtx );
        ready = true;
        lock.unlock();
        condition.notify_one();
    });

    std::unique_lock<std::mutex> lock( mtx );
    while ( !ready )
    {
        condition.wait( lock );
    }

    std::cout << "ready " << ready << std::endl;

    t1.join();

    return 0;
}
