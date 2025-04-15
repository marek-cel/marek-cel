#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <cmath>

#include <RollPitchYaw.h>
#include <Vector3.h>

class Matrix3x3
{
public:

    double _m[3][3] = {0.0}; ///< 3x3 matrix elements in row-major order

    Matrix3x3(double xx = 1.0, double xy = 0.0, double xz = 0.0,
              double yx = 0.0, double yy = 1.0, double yz = 0.0,
              double zx = 0.0, double zy = 0.0, double zz = 1.0)
    {
        _m[0][0] = xx; _m[0][1] = xy; _m[0][2] = xz;
        _m[1][0] = yx; _m[1][1] = yy; _m[1][2] = yz;
        _m[2][0] = zx; _m[2][1] = zy; _m[2][2] = zz;
    }

    Matrix3x3(const RollPitchYaw& rpy)
    {
        setRollPitchYaw(rpy);
    }

    void setRollPitchYaw(const RollPitchYaw& rpy)
    {
        double sinPhi = sin(rpy._phi);
        double cosPhi = cos(rpy._phi);
        double sinTht = sin(rpy._tht);
        double cosTht = cos(rpy._tht);
        double sinPsi = sin(rpy._psi);
        double cosPsi = cos(rpy._psi);

        double sinPhiSinTht = sinPhi * sinTht;
        double cosPhiSinTht = cosPhi * sinTht;

        _m[0][0] =  cosTht * cosPsi;
        _m[0][1] =  cosTht * sinPsi;
        _m[0][2] = -sinTht;

        _m[1][0] = -(cosPhi * sinPsi) + (sinPhiSinTht * cosPsi);
        _m[1][1] =  (cosPhi * cosPsi) + (sinPhiSinTht * sinPsi);
        _m[1][2] =  (sinPhi * cosTht);

        _m[2][0] =  (sinPhi * sinPsi) + (cosPhiSinTht * cosPsi);
        _m[2][1] = -(sinPhi * cosPsi) + (cosPhiSinTht * sinPsi);
        _m[2][2] =  (cosPhi * cosTht);
    }

    RollPitchYaw getRollPitchYaw() const
    {
        RollPitchYaw result;

        double sinTht = -_m[0][2];
        double cosTht = sqrt(1.0 - std::min(1.0, sinTht*sinTht));

        result._tht = atan2(sinTht, cosTht);

        if ( cosTht > 0.0 )
        {
            result._phi = atan2(_m[1][2],  _m[2][2]);
            result._psi = atan2(_m[0][1],  _m[0][0]);
        }
        else
        {
            result._phi = atan2(_m[1][0], -_m[2][0]);
            result._psi = 0.0;
        }

        return result;
    }

    Matrix3x3 operator*(const Matrix3x3& mat) const
    {
        Matrix3x3 result;

        for (int r = 0; r < 3; ++r)
        {
            for (int c = 0; c < 3; ++c)
            {
                result._m[r][c] = _m[r][0] * mat._m[0][c] +
                                  _m[r][1] * mat._m[1][c] +
                                  _m[r][2] * mat._m[2][c];
            }
        }

        return result;
    }

    Vector3 operator*(const Vector3& vec) const
    {
        return Vector3(
            _m[0][0] * vec.x() + _m[0][1] * vec.y() + _m[0][2] * vec.z(),
            _m[1][0] * vec.x() + _m[1][1] * vec.y() + _m[1][2] * vec.z(),
            _m[2][0] * vec.x() + _m[2][1] * vec.y() + _m[2][2] * vec.z());
    }
};

#endif // MATRIX3X3_H
