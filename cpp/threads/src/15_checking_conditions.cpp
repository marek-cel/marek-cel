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
        std::cout << "t1 acquiring lock" << std::endl;
        std::unique_lock<std::mutex> lock( mtx );
        std::cout << "t1 acquired lock" << std::endl;
        ready = true;
        lock.unlock();
        std::cout << "t1 released lock; notyfying" << std::endl;
        condition.notify_one();
    });

    std::unique_lock<std::mutex> lock( mtx );
    std::cout << "main thread acquired lock; waiting" << std::endl;

    std::cout << "main thread waiting" << std::endl;
    condition.wait( lock, [&](){ return ready; } );
    std::cout << "main thread finished waiting" << std::endl;

    std::cout << "ready " << ready << std::endl;

    t1.join();

    return 0;
}
