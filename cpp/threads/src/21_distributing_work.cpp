#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

// Leibniz formula
double calc_pi( int start, int stop )
{
    double result = 0.0;

    for ( int i = start; i < stop; ++i )
    {
        double term = 1.0 / ( i * 2 + 1 );
        int sign = i % 2 == 0 ? 1 : -1;
        result += sign * term;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    const int CONCURENCY = std::thread::hardware_concurrency();

    std::cout << CONCURENCY << std::endl;

    std::vector< std::shared_future<double> > vf;

    for ( int i = 0; i < CONCURENCY; ++i )
    {
        vf.push_back( std::async( std::launch::async, calc_pi, i * 1e8, (i+1) * 1e8 ) );
    }

    double pi = 0.0;

    for ( auto &f : vf )
    {
        pi += f.get();
    }

    pi *= 4.0;

    std::cout << std::setprecision(15) << pi << std::endl;

    return 0;
}
