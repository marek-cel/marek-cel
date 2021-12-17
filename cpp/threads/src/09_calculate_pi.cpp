#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>

////////////////////////////////////////////////////////////////////////////////

// Leibniz formula
double calc_pi( int terms )
{
    double result = 0.0;

    for ( int i = 0; i < terms; ++i )
    {
        double term = 1.0 / ( i * 2 + 1 );
        int sign = i % 2 == 0 ? 1 : -1;
        result += sign * term;
    }

    return 4.0 * result;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    std::cout << std::setprecision(15) << calc_pi( 1e9 ) << std::endl;

    return 0;
}
