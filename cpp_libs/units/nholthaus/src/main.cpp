#include <iostream>

#include <units.h>

using namespace units::literals;
// using namespace units::math;

int main(int argc, char* argv[])
{
	auto tangential_velocity = 1.0_rad_per_s * 2.0_m;
	std::cout << "Tangential Velocity: " << tangential_velocity << std::endl;

    return 0;
}