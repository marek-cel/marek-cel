#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>

////////////////////////////////////////////////////////////////////////////////

// Leibniz formula
double calc_pi( int terms )
{
    double result = 0.0;

    int sign = -1;

    if ( terms < 1 )
    {
        throw std::runtime_error("Terms cannot be less than one");
    }

    for ( int i = 0; i < terms; ++i )
    {
        double term = 1.0 / ( i * 2 + 1 );
        result += sign * term;
        sign *= -1;
    }

    return 4.0 * result;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    std::packaged_task<double(int)> task1( calc_pi );

    std::future<double> future1 = task1.get_future();

    std::thread t1( std::move( task1 ), 1e8 );

    try
    {
        double result = future1.get();
        std::cout << std::setprecision(15) << result << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    t1.join();

    return 0;
}
