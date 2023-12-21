#include <iostream>

#include <boost/units/base_dimension.hpp>
#include <boost/units/derived_dimension.hpp>

#include <boost/units/physical_dimensions/length.hpp>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    boost::units::length_dimension L;

    std::cout
//              << "L             = " << L << std::endl
//              << "L+L           = " << L+L << std::endl
//              << "L-L           = " << L-L << std::endl
//              << "L/L           = " << L/L << std::endl
//              << "meter*meter   = " << meter*meter << std::endl
//              << "M*(L/T)*(L/T) = " << M*(L/T)*(L/T) << std::endl
//              << "M*(L/T)^2     = " << M*pow<2>(L/T) << std::endl
//              << "L^3           = " << pow<3>(L) << std::endl
//              << "L^(3/2)       = " << pow<static_rational<3,2> >(L)
//              << std::endl
//              << "2vM           = " << root<2>(M) << std::endl
//              << "(3/2)vM       = " << root<static_rational<3,2> >(M)
              << std::endl;

    return 0;
}
