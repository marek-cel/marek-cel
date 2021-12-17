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
        double result = calc_pi( terms );
        prom.set_value( result );
    };

    std::thread t1( func, 1e8 );

    std::future<double> fut = prom.get_future();

    std::cout << std::setprecision(15) << fut.get() << std::endl;

    t1.join();

    return 0;
}
