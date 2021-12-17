#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

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

    T pop()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _signal.wait( lock, [&](){ return !_queue.empty(); } );

        T item = _queue.front();
        _queue.pop();

        lock.unlock();
        _signal.notify_one();

        return item;
    }

private:

    int _max_size;

    std::queue<T> _queue;
    std::mutex _mutex;
    std::condition_variable _signal;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    blocking_queue<int> bq( 3 );

    std::thread t1([&]()
    {
        for ( int i = 0; i < 9; ++i )
        {
            bq.push(i);
            std::cout << "Produced " << i << std::endl;
        }
    });



    std::thread t2([&]()
    {
        for ( int i = 0; i < 9; ++i )
        {
            int item = bq.pop();
            std::cout << "Consumed " << item << std::endl;
        }
    });

    t1.join();
    t2.join();

    return 0;
}
