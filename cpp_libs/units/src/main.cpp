#include <iostream>

#include <units.h>

using namespace units::literals;

////////////////////////////////////////////////////////////////////////////////

void test();

////////////////////////////////////////////////////////////////////////////////

template <typename TYPE, unsigned int SIZE>
class VectorN
{
public:

    static constexpr unsigned int kSize = SIZE;

    inline TYPE operator()(unsigned int index) const
    {
        return _elements[index];
    }

    inline TYPE& operator()(unsigned int index)
    {
        return _elements[index];
    }

    VectorN<TYPE, SIZE> operator+(const VectorN<TYPE, SIZE>& vect) const
    {
        VectorN<TYPE, SIZE> result(*this);
        result.Add(vect);
        return result;
    }

    VectorN<TYPE, SIZE> operator*(double value) const
    {
        VectorN<TYPE, SIZE> result(*this);
        result.MultiplyByValue(value);
        return result;
    }

protected:

    TYPE _elements[kSize] = { TYPE{0} };    ///< vector items

    void Add(const VectorN<TYPE, SIZE>& vect)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] += vect._elements[i];
        }
    }

    void MultiplyByValue(double value)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] *= value;
        }
    }
};

////////////////////////////////////////////////////////////////////////////////

template <typename TYPE>
class Vector3 : public VectorN<TYPE, 3>
{
public:

    inline TYPE& x() { return this->_elements[0]; }
    inline TYPE& y() { return this->_elements[1]; }
    inline TYPE& z() { return this->_elements[2]; }

    inline const TYPE x() const { return this->_elements[0]; }
    inline const TYPE y() const { return this->_elements[1]; }
    inline const TYPE z() const { return this->_elements[2]; }

    Vector3<TYPE> operator+(const Vector3<TYPE>& vect) const
    {
        Vector3<TYPE> result(*this);
        result.Add(vect);
        return result;
    }

    Vector3<TYPE> operator*(double value) const
    {
        Vector3<TYPE> result(*this);
        result.MultiplyByValue(value);
        return result;
    }
};

using Vector3d = Vector3<double>;

////////////////////////////////////////////////////////////////////////////////

template <typename TYPE>
class UnitsVector3 : public Vector3<TYPE>
{
public:

    UnitsVector3(TYPE x = TYPE{0}, TYPE y = TYPE{0}, TYPE z = TYPE{0})
    {
        this->x() = x;
        this->y() = y;
        this->z() = z;
    }

    template <class RHS>
    UnitsVector3(const UnitsVector3<RHS>& rhs)
    {
        //using UnitsLhs = typename units::traits::unit_t_traits<LHS>::unit_type;
        using UnitsRhs = typename units::traits::unit_t_traits<RHS>::unit_type;

        this->x() = rhs.x();
        this->y() = rhs.y();
        this->z() = rhs.z();
    }

    UnitsVector3<TYPE> operator+(const UnitsVector3<TYPE>& vect) const
    {
        UnitsVector3<TYPE> result(*this);
        result.Add(vect);
        return result;
    }

    UnitsVector3<TYPE> operator*(double value) const
    {
        UnitsVector3<TYPE> result(*this);
        result.MultiplyByValue(value);
        return result;
    }

    template <class RHS>
    auto operator=(const UnitsVector3<RHS>& rhs)
    {
        //using UnitsLhs = typename units::traits::unit_t_traits<LHS>::unit_type;
        using UnitsRhs = typename units::traits::unit_t_traits<RHS>::unit_type;

        this->x() = rhs.x();
        this->y() = rhs.y();
        this->z() = rhs.z();
        return *this;
    }
};

template <class LHS, class RHS>
auto operator*(const UnitsVector3<LHS> &vect, RHS value)
{
    using UnitsLhs = typename units::traits::unit_t_traits<LHS>::unit_type;
    using UnitsRhs = typename units::traits::unit_t_traits<RHS>::unit_type;

    UnitsVector3< units::unit_t<units::compound_unit<UnitsLhs, UnitsRhs>> > result;
    result.x() = vect.x() * value;
    result.y() = vect.y() * value;
    result.z() = vect.z() * value;
    return result;
}

template <class LHS, class RHS>
auto operator*(const UnitsVector3<LHS> &lhs, UnitsVector3<RHS> rhs)
{
    using UnitsLhs = typename units::traits::unit_t_traits<LHS>::unit_type;
    using UnitsRhs = typename units::traits::unit_t_traits<RHS>::unit_type;

    UnitsVector3< units::unit_t<units::compound_unit<UnitsLhs, UnitsRhs>> > result;
    result.x() = lhs.x() * rhs.x();
    result.y() = lhs.y() * rhs.y();
    result.z() = lhs.z() * rhs.z();
    return result;
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    std::cout << "Hello Units!" << std::endl;


    std::cout << std::endl;
    VectorN<double, 3> vn_1;
    vn_1(0) = 1.0;
    vn_1(1) = 2.0;
    vn_1(2) = 3.0;
    std::cout << "vn_1= " << vn_1(0) << ", " << vn_1(1) << ", " << vn_1(2) << std::endl;
    VectorN<double, 3> vn_2;
    vn_2(0) = 4.0;
    vn_2(1) = 5.0;
    vn_2(2) = 6.0;
    std::cout << "vn_2= " << vn_2(0) << ", " << vn_2(1) << ", " << vn_2(2) << std::endl;
    VectorN<double, 3> vn_3 = vn_1 + vn_2;
    std::cout << "vn_3= " << vn_3(0) << ", " << vn_3(1) << ", " << vn_3(2) << std::endl;
    VectorN<double, 3> vn_4 = vn_1 * 2.0;
    std::cout << "vn_4= " << vn_4(0) << ", " << vn_4(1) << ", " << vn_4(2) << std::endl;

    std::cout << std::endl;
    Vector3d v3d_1;
    v3d_1.x() = 1.0;
    v3d_1.y() = 2.0;
    v3d_1.z() = 3.0;
    std::cout << "v3d_1= " << v3d_1(0) << ", " << v3d_1(1) << ", " << v3d_1(2) << std::endl;
    Vector3d v3d_2;
    v3d_2.x() = 4.0;
    v3d_2.y() = 5.0;
    v3d_2.z() = 6.0;
    std::cout << "v3d_2= " << v3d_2(0) << ", " << v3d_2(1) << ", " << v3d_2(2) << std::endl;
    Vector3d v3d_3 = v3d_1 + v3d_2;
    std::cout << "v3d_3= " << v3d_3(0) << ", " << v3d_3(1) << ", " << v3d_3(2) << std::endl;
    Vector3d v3d_4 = v3d_1 * 2.0;
    std::cout << "v3d_4= " << v3d_4(0) << ", " << v3d_4(1) << ", " << v3d_4(2) << std::endl;

    std::cout << std::endl;
    UnitsVector3<units::length::meter_t> v3m_1;
    v3m_1.x() = 1.0_m;
    v3m_1.y() = 2.0_m;
    v3m_1.z() = 3.0_m;
    std::cout << "v3m_1= " << v3m_1(0) << ", " << v3m_1(1) << ", " << v3m_1(2) << std::endl;
    UnitsVector3<units::length::meter_t> v3m_2;
    v3m_2.x() = 4.0_m;
    v3m_2.y() = 5.0_m;
    v3m_2.z() = 6.0_m;
    std::cout << "v3m_2= " << v3m_2(0) << ", " << v3m_2(1) << ", " << v3m_2(2) << std::endl;
    UnitsVector3<units::length::meter_t> v3m_3 = v3m_1 + v3m_2;
    std::cout << "v3m_3= " << v3m_3(0) << ", " << v3m_3(1) << ", " << v3m_3(2) << std::endl;
    UnitsVector3<units::length::meter_t> v3m_4 = v3m_1 * 2.0;
    std::cout << "v3m_4= " << v3m_4(0) << ", " << v3m_4(1) << ", " << v3m_4(2) << std::endl;
    UnitsVector3<units::area::square_meter_t> v3a_1 = v3m_1 * 2.0_m;
    std::cout << "v3a_1= " << v3a_1(0) << ", " << v3a_1(1) << ", " << v3a_1(2) << std::endl;

    std::cout << std::endl;
    UnitsVector3<units::length::meter_t> r(1.0_m, 2.0_m, 3.0_m);
    UnitsVector3<units::force::newton_t> f(4.0_N, 5.0_N, 6.0_N);
    UnitsVector3<units::torque::newton_meter_t> t1;
    t1 = f * r;
    UnitsVector3<units::torque::newton_meter_t> t2 = f * r;
    auto t3 = f * r;
    std::cout << "t1= " << t1(0) << ", " << t1(1) << ", " << t1(2) << std::endl;
    std::cout << "t2= " << t2(0) << ", " << t2(1) << ", " << t2(2) << std::endl;
    std::cout << "t3= " << t3(0) << ", " << t3(1) << ", " << t3(2) << std::endl;


    return 0;
}

void test()
{
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

    std::cout << "a= " << static_cast<double>(a) << std::endl;
    std::cout << "d= " << static_cast<double>(d) << std::endl;
}
