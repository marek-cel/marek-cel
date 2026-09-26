#include <iostream>

#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

// using namespace mp_units;
// using namespace mp_units::si::unit_symbols;
// using mp_units::angular::unit_symbols::deg;
// using mp_units::angular::unit_symbols::rad;

int main(int argc, char* argv[])
{
    using namespace mp_units;
    using namespace mp_units::si::unit_symbols;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::angular::unit_symbols::rad;

	std::cout << "Hello, units!" << std::endl;
    std::cout << std::endl;

    quantity l = 1.0 * m;
    quantity t = 10.0 * s;
    quantity v = l / t;

    std::cout << "Length: " << l << std::endl;
    std::cout << "Time: " << t << std::endl;
    std::cout << "Velocity: " << v << std::endl;

    std::cout << std::endl;

    // https://mpusz.github.io/mp-units/2.3/users_guide/systems/strong_angular_system/
    quantity r = 0.5 * m;
    quantity omega = 2.0 * rad / s;
    quantity v_tang = r * omega / (1 * isq_angle::cotes_angle);

    std::cout << "Radius: " << r << std::endl;
    std::cout << "Angular velocity: " << omega << std::endl;
    std::cout << "Tangential velocity: " << v_tang << std::endl;

    return 0;
}