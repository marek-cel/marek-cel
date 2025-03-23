#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>

#include <units.h>

using namespace std;

using namespace units::literals;

int main()
{
    std::cout << "Hello, libERFA!" << std::endl;

    units::length::meter_t l1 = 1.0_ft;
    std::cout << "l1 = " << l1 << std::endl;

    return 0;
}
