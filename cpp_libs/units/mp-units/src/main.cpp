#include <iostream>

#include <mp-units/systems/si.h>
// #include <mp-units/ostream.h>

using namespace mp_units;
using namespace mp_units::si::unit_symbols;

int main(int argc, char* argv[])
{
	std::cout << "Hello, units!" << std::endl;

    quantity l = 1.0 * m;
    quantity t = 10.0 * s;
    quantity v = l / t;

    std::cout << "Length: " << l << std::endl;
    std::cout << "Time: " << t << std::endl;
    std::cout << "Velocity: " << v << std::endl;

    quantity omega = 2.0 * M_PI * rad / s;
    quantity radius = 5.0 * m;
    quantity tangential_velocity = omega * radius;

    std::cout << "Angular velocity: " << omega << std::endl;
    std::cout << "Radius: " << radius << std::endl;
    std::cout << "Tangential velocity: " << tangential_velocity << std::endl;

    return 0;
}