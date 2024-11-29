#include <iostream>

#include <boost/units/systems/si/angular_velocity.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <boost/units/systems/si/io.hpp>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << std::endl;

    boost::units::quantity<boost::units::si::angular_velocity> omega(1.0 * boost::units::si::radian_per_second);
    boost::units::quantity<boost::units::si::length> r(1.0 * boost::units::si::meter);

    boost::units::quantity<boost::units::si::velocity> v = omega * r;

    //auto v = omega * r;

    std::cout << "v = " << v << std::endl;

    return 0;
}
