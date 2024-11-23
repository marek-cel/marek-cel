#include <iostream>

#include <units.h>

using namespace units::literals;

int main(int argc, char* argv[])
{
    std::cout << "Hello Units!" << std::endl;

    units::length::meter_t l = 1.0_m;
    std::cout << "l = " << l << std::endl;

    l = 1.0_ft;
    std::cout << "l = " << l << std::endl;

    units::force::newton_t f = 1.0_N;
    units::torque::newton_meter_t t = f * l;
    std::cout << "t = " << t << std::endl;
    std::cout << "t = " << static_cast<double>(t) << std::endl;

    units::angle::radian_t a = 1.0_rad * M_PI;
    units::angle::degree_t d = a;
    std::cout << "d = " << d << std::endl;
    std::cout << "d = " << d() << std::endl;
    auto str = units::angle::to_string(d);
    std::cout << "d = " << str << std::endl;

    return 0;
}
