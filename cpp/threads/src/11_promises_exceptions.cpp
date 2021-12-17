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

    std::promise<double> prom;

    auto func = [&]( int terms )
    {
        try
        {
            double result = calc_pi( terms );
            prom.set_value( result );
        }
        catch (const std::exception &e )
        {
            std::cout << e.what() << std::endl;
            prom.set_exception( std::current_exception() );
        }
    };

    std::thread t1( func, 0 );

    std::future<double> fut = prom.get_future();

    try
    {
        std::cout << std::setprecision(15) << fut.get() << std::endl;
    }
    catch (const std::exception &e )
    {
        std::cout << e.what() << std::endl;
    }

    t1.join();

    return 0;
}
