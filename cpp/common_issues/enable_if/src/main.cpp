#include <iostream>

#include <units.h>

using namespace units::literals;
using namespace units::math;

template <typename TYPE>
class Vector3
{
public:

    Vector3<TYPE> operator+(const Vector3<TYPE>& v)
    {
        Vector3<TYPE> result;
        result._x = this->_x + v._x;
        result._y = this->_y + v._y;
        result._z = this->_z + v._z;
        return result;
    }

    template <typename TYPE2, std::enable_if_t<
    units::traits::is_unit_t<TYPE>::value
    ,int> = 0>
    auto operator*(const TYPE& x)
    {
        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<TYPE2>::unit_type
                >
            >
        > result;

        result._x = this->_x * x;
        result._y = this->_y * x;
        result._z = this->_z * x;
        return result;
    }


    TYPE _x {0};
    TYPE _y {0};
    TYPE _z {0};
};

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

    Vector3<units::acceleration::meters_per_second_squared_t> a;
    Vector3<units::velocity::meters_per_second_t> v;

    a._x = 1.0_mps_sq;
    a._y = 2.0_mps_sq;
    a._z = 3.0_mps_sq;

    v = v + a * 2.0_s;

    std::cout << "v: (" << v._x << ", " << v._y << ", " << v._z << ")" << std::endl;

    return 0;
}
