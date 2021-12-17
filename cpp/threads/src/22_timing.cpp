#include <chrono>
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

    std::chrono::time_point start1 = std::chrono::steady_clock::now();

    for ( int i = 0; i < CONCURENCY; ++i )
    {
        vf.push_back( std::async( std::launch::async, calc_pi, i * 1e8, (i+1) * 1e8 ) );
    }

    double pi1 = 0.0;

    for ( auto &f : vf )
    {
        pi1 += f.get();
    }

    pi1 *= 4.0;

    std::chrono::time_point end1 = std::chrono::steady_clock::now();

    std::cout << std::setprecision(15) << pi1 << std::endl;

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>( end1 - start1 ).count() << std::endl;

    ///////////////////////
    std::cout << std::endl;
    ///////////////////////

    std::chrono::time_point start2 = std::chrono::steady_clock::now();

    double pi2 = 4.0 * calc_pi( 0, CONCURENCY * 1e8 );

    std::chrono::time_point end2 = std::chrono::steady_clock::now();

    std::cout << std::setprecision(15) << pi2 << std::endl;

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>( end2 - start2 ).count() << std::endl;


    return 0;
}
