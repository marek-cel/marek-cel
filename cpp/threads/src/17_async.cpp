#include <future>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

int work( int id )
{
    for ( int i = 0; i < 5; ++i )
    {
        std::cout << "Running " << id << std::endl;
    }

    return 2 * id;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    std::future<int> f1 = async( std::launch::async, work, 0 );
    std::future<int> f2 = async( std::launch::async, work, 1 );

    std::cout << f1.get() << std::endl;
    std::cout << f2.get() << std::endl;

    return 0;
}
