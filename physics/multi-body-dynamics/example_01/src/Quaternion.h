#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>

#include <RollPitchYaw.h>
#include <Vector3.h>

class Quaternion
{
public:

    double _e0 = 1.0;   ///< quaternion e0 (w) component
    double _ex = 0.0;   ///< quaternion ex (x) component
    double _ey = 0.0;   ///< quaternion ey (y) component
    double _ez = 0.0;   ///< quaternion ez (z) component

    Quaternion(double e0 = 1.0, double ex = 0.0,
               double ey = 0.0, double ez = 0.0)
    {
        _e0 = e0;
        _ex = ex;
        _ey = ey;
        _ez = ez;
    }

    Quaternion(const RollPitchYaw& rpy)
    {
        setRollPitchYaw(rpy);
    }

    RollPitchYaw getRollPitchYaw() const
    {
        RollPitchYaw result;
        double sin_tht_2 = _e0*_ey - _ex*_ez;
        if(sin_tht_2 >= 0.5)
        {
            result._phi =  2.0 * asin(_ex / cos(M_PI_4));
            result._tht =  0.5 * M_PI;
            result._psi =  0.0;
        }
        else if (sin_tht_2 <= -0.5)
        {
            result._phi =  2.0 * asin(_ex / cos(M_PI_4));
            result._tht = -0.5 * M_PI;
            result._psi =  0.0;
        }
        else
        {
            result._phi = atan2(2.0*(_e0*_ex + _ey*_ez), 1.0 - 2.0*(_ex*_ex + _ey*_ey));
            result._tht = asin(2.0*sin_tht_2);
            result._psi = atan2(2.0*(_e0*_ez + _ex*_ey), 1.0 - 2.0*(_ey*_ey + _ez*_ez));
        }
        return result;
    }

    double getLength() const
    {
        return sqrt(_e0*_e0 + _ex*_ex + _ey*_ey + _ez*_ez);
    }

    void normalize()
    {
        double length = getLength();
        if (length > 0.0)
        {
            _e0 /= length;
            _ex /= length;
            _ey /= length;
            _ez /= length;
        }
    }

    Quaternion getInverse() const
    {
        Quaternion result;
        double length = _e0*_e0 + _ex*_ex + _ey*_ey + _ez*_ez;
        if (length > 0.0)
        {
            result._e0 = _e0 / length;
            result._ex = -_ex / length;
            result._ey = -_ey / length;
            result._ez = -_ez / length;
        }

        result.normalize();

        return result;
    }

    Quaternion getDerivative(const Vector3& omega, double lambda = 0.0) const
    {
        Quaternion result;

        result._e0 = -0.5 * (_ez*omega.z() + _ey*omega.y() + _ex*omega.x());
        result._ex = -0.5 * (_ez*omega.y() - _ey*omega.z() - _e0*omega.x());
        result._ey = -0.5 * (_ex*omega.z() - _e0*omega.y() - _ez*omega.x());
        result._ez = -0.5 * (_ey*omega.x() - _e0*omega.z() - _ex*omega.y());

        if (lambda > 0.0)
        {
            double epsilon = 1.0 - (_e0*_e0 + _ex*_ex + _ey*_ey + _ez*_ez);
            double lambda_epsilon = lambda * epsilon;

            result._e0 += lambda_epsilon * _e0;
            result._ex += lambda_epsilon * _ex;
            result._ey += lambda_epsilon * _ey;
            result._ez += lambda_epsilon * _ez;
        }

        return result;
    }

    void setRollPitchYaw(const RollPitchYaw& rpy)
    {
        double phi_2 = rpy._phi / 2.0;
        double tht_2 = rpy._tht / 2.0;
        double psi_2 = rpy._psi / 2.0;

        double sin_phi_2 = sin(phi_2);
        double cos_phi_2 = cos(phi_2);
        double sin_tht_2 = sin(tht_2);
        double cos_tht_2 = cos(tht_2);
        double sin_psi_2 = sin(psi_2);
        double cos_psi_2 = cos(psi_2);

        double cos_phi_2_cos_psi_2 = cos_phi_2 * cos_psi_2;
        double cos_phi_2_sin_psi_2 = cos_phi_2 * sin_psi_2;
        double sin_phi_2_sin_psi_2 = sin_phi_2 * sin_psi_2;
        double sin_phi_2_cos_psi_2 = sin_phi_2 * cos_psi_2;

        _e0 = (cos_phi_2_cos_psi_2 * cos_tht_2) + (sin_phi_2_sin_psi_2 * sin_tht_2);
        _ex = (sin_phi_2_cos_psi_2 * cos_tht_2) - (cos_phi_2_sin_psi_2 * sin_tht_2);
        _ey = (cos_phi_2_cos_psi_2 * sin_tht_2) + (sin_phi_2_sin_psi_2 * cos_tht_2);
        _ez = (cos_phi_2_sin_psi_2 * cos_tht_2) - (sin_phi_2_cos_psi_2 * sin_tht_2);

        double length = sqrt(_e0*_e0 + _ex*_ex + _ey*_ey + _ez*_ez);
        if (length > 0.0)
        {
            _e0 = _e0 / length;
            _ex = _ex / length;
            _ey = _ey / length;
            _ez = _ez / length;
        }
    }

    Quaternion operator+(const Quaternion& quat) const
    {
        Quaternion result;
        result._e0 = _e0 + quat._e0;
        result._ex = _ex + quat._ex;
        result._ey = _ey + quat._ey;
        result._ez = _ez + quat._ez;
        return result;
    }

    Quaternion operator-(const Quaternion& quat) const
    {
        Quaternion result;
        result._e0 = _e0 - quat._e0;
        result._ex = _ex - quat._ex;
        result._ey = _ey - quat._ey;
        result._ez = _ez - quat._ez;
        return result;
    }

    Quaternion operator*(double val) const
    {
        Quaternion result;
        result._e0 = _e0 * val;
        result._ex = _ex * val;
        result._ey = _ey * val;
        result._ez = _ez * val;
        return result;
    }

    Quaternion operator*(const Quaternion& quat) const
    {
        Quaternion result;
        result._e0 = _e0*quat._e0 - _ex*quat._ex - _ey*quat._ey - _ez*quat._ez;
        result._ex = _e0*quat._ex + _ex*quat._e0 + _ey*quat._ez - _ez*quat._ey;
        result._ey = _e0*quat._ey - _ex*quat._ez + _ey*quat._e0 + _ez*quat._ex;
        result._ez = _e0*quat._ez + _ex*quat._ey - _ey*quat._ex + _ez*quat._e0;
        return result;
    }

    Vector3 operator*(const Vector3& vec) const
    {
        Vector3 result;
        result.x() = _e0*vec.x() + _ey*vec.z() - _ez*vec.y();
        result.y() = _e0*vec.y() + _ez*vec.x() - _ex*vec.z();
        result.z() = _e0*vec.z() + _ex*vec.y() - _ey*vec.x();
        return result;
    }

    const Quaternion& operator=(const Quaternion& quat)
    {
        _e0 = quat._e0;
        _ex = quat._ex;
        _ey = quat._ey;
        _ez = quat._ez;
        return *this;
    }

    Quaternion& operator+=(const Quaternion& quat)
    {
        *this = *this + quat;
        return *this;
    }
};

#endif // QUATERNION_H
