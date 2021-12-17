#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

std::mutex g_mtx;

////////////////////////////////////////////////////////////////////////////////

int fun( int id )
{
    std::unique_lock<std::mutex> lock( g_mtx );
    std::cout << "Starting " << id << std::endl;
    lock.unlock();
    std::this_thread::sleep_for( std::chrono::seconds( 3 ) );

    return 2*id;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    std::vector< std::shared_future<int> > vf;

    for ( unsigned int i = 0; i < std::thread::hardware_concurrency(); ++i )
    {
        vf.push_back( std::async( std::launch::async, fun, i ) );
    }

    for ( auto &f : vf )
    {
        std::cout << f.get() << std::endl;
    }

    return 0;
}
