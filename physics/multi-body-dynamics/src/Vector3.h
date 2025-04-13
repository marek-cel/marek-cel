#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3
{
public:

    double _v[3] = {0.0}; ///< vector elements in row-major order

    Vector3(double x = 0.0, double y = 0.0, double z = 0.0)
    {
        _v[0] = x;
        _v[1] = y;
        _v[2] = z;
    }

    double getLength() const
    {
        return sqrt(_v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2]);
    }

    Vector3 getNormalized() const
    {
        Vector3 result;
        double length = getLength();
        if (length > 1.0e-9)
        {
            result._v[0] = _v[0] / length;
            result._v[1] = _v[1] / length;
            result._v[2] = _v[2] / length;
        }
        else
        {
            result._v[0] = 0.0;
            result._v[1] = 0.0;
            result._v[2] = 0.0;
        }
        return result;
    }

    inline double x() const { return _v[0]; }
    inline double y() const { return _v[1]; }
    inline double z() const { return _v[2]; }

    inline double& x() { return _v[0]; }
    inline double& y() { return _v[1]; }
    inline double& z() { return _v[2]; }

    Vector3 operator+(const Vector3& vec) const
    {
        return Vector3(_v[0] + vec._v[0], _v[1] + vec._v[1], _v[2] + vec._v[2]);
    }

    Vector3 operator-(const Vector3& vec) const
    {
        return Vector3(_v[0] - vec._v[0], _v[1] - vec._v[1], _v[2] - vec._v[2]);
    }

    Vector3 operator*(double val) const
    {
        return Vector3(_v[0] * val, _v[1] * val, _v[2] * val);
    }

    double operator*(const Vector3& vec) const
    {
        return _v[0]*vec._v[0] + _v[1]*vec._v[1] + _v[2]*vec._v[2];
    }

    Vector3 operator/(double val) const
    {
        return Vector3(_v[0] / val, _v[1] / val, _v[2] / val);
    }

    Vector3 operator%(const Vector3& vec) const
    {
        Vector3 result;
        result._v[0] = _v[1] * vec._v[2] - _v[2] * vec._v[1];
        result._v[1] = _v[2] * vec._v[0] - _v[0] * vec._v[2];
        result._v[2] = _v[0] * vec._v[1] - _v[1] * vec._v[0];
        return result;
    }

    const Vector3& operator=(const Vector3& vec)
    {
        _v[0] = vec._v[0];
        _v[1] = vec._v[1];
        _v[2] = vec._v[2];
        return *this;
    }

    Vector3& operator+=(const Vector3& vec)
    {
        *this = *this + vec;
        return *this;
    }

    Vector3& operator-=(const Vector3& vec)
    {
        *this = *this - vec;
        return *this;
    }
};


#endif // VECTOR3_H
