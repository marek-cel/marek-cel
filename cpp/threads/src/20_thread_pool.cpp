#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

std::mutex g_mtx;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
class blocking_queue
{
public:

    blocking_queue( int max_size ) : _max_size( max_size ) {}

    void push( T item )
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _signal.wait( lock, [&](){ return _queue.size() < static_cast<size_t>(_max_size); } );

        _queue.push( item );

        lock.unlock();
        _signal.notify_one();
    }

    void pop()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _signal.wait( lock, [&](){ return !_queue.empty(); } );

        T item = _queue.front();
        _queue.pop();

        lock.unlock();
        _signal.notify_one();
    }

    T front()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _signal.wait( lock, [this](){ return !_queue.empty(); } );

        return _queue.front();
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.size();
    }

private:

    int _max_size;

    std::queue<T> _queue;
    std::mutex _mutex;
    std::condition_variable _signal;
};

////////////////////////////////////////////////////////////////////////////////

int fun( int id )
{
    int seconds = static_cast<int>( ( 5.0 * rand() ) / RAND_MAX + 3 );

    std::unique_lock<std::mutex> lock( g_mtx );
    std::cout << "Starting " << id << " " << seconds << "s" << std::endl;
    lock.unlock();

    std::this_thread::sleep_for( std::chrono::seconds( seconds ) );

    return id;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    srand(time(NULL));

    blocking_queue< std::shared_future<int> > qf( 2 );

    const int number_of_threads = 20;

    std::thread t( [&]()
    {
        for ( int i = 0; i < number_of_threads; ++i )
        {
            std::shared_future<int> f = qf.front();
            int value = f.get();
            qf.pop();
            std::cout << ">>> " << value << std::endl;
        }
    });

    for ( int i = 0; i < number_of_threads; ++i )
    {
        qf.push( std::async( std::launch::async, fun, i ) );
    }

    t.join();

    return 0;
}
