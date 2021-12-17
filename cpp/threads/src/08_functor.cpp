#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

////////////////////////////////////////////////////////////////////////////////

class Functor
{
public:

    void operator()()
    {
        for ( int i = 0; i < 1e6; i++ )
        {
            std::lock_guard<std::mutex> guard(mtx);
            ++count;
            // lock guard is out of scope and unlocks mutex
            // this can also be done with std::unique_lock
        }
    }

    int getCount() { return count; }

private:

    int count { 0 };
    std::mutex mtx;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    Functor obj;

    // constructs new thread objects
    std::thread t1( std::ref( obj ) );
    std::thread t2( std::ref( obj ) );

    t1.join();
    t2.join();

    std::cout << obj.getCount() << std::endl;

    return 0;
}
