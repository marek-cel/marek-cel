#include <iostream>

#include <units.h>

using namespace units::literals;

int main(int argc, char* argv[])
{
	std::cout << "Hello, units!" << std::endl;

    units::length::meters l = 1.0_m;
    units::time::seconds t = 10.0_s;
    units::velocity::meters_per_second v = l / t;

    std::cout << "Length: " << l << std::endl;
    std::cout << "Time: " << t << std::endl;
    std::cout << "Velocity: " << v << std::endl;

    return 0;
}