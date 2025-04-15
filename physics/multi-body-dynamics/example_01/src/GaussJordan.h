#ifndef GAUSSJORDAN_H
#define GAUSSJORDAN_H

#include <cmath>

#include <Matrix3x3.h>
#include <Vector3.h>

bool solveGaussJordan(const Matrix3x3& mtr, const Vector3& rhs, Vector3* x, double eps = 1.0e-9)
{
    Matrix3x3 mtr_temp = mtr;
    Vector3   rhs_temp = rhs;

    for (unsigned int r = 0; r < 3; ++r)
    {
        // run along diagonal, swapping rows to move zeros (outside the diagonal) downwards
        if (fabs(mtr_temp._m[r][r]) < fabs(eps))
        {
            if ( r < 3 - 1 )
            {
                std::swap(mtr_temp._m[r], mtr_temp._m[r+1]);
                std::swap(rhs_temp._v[r], rhs_temp._v[r+1]);
            }
            else
            {
                return false;
            }
        }

        // value on diagonal A(r,r)
        double a_rr = mtr_temp._m[r][r];
        double a_rr_inv = 1.0 / a_rr;

        // deviding current row by value on diagonal
        for (unsigned int c = 0; c < 3; ++c)
        {
            mtr_temp._m[r][c] *= a_rr_inv;
        }

        rhs_temp._v[r] *= a_rr_inv;

        // substracting current row from others rows
        // for every row current row is multiplied by A(i,r)
        // where r stands for row that is substracted from other rows
        // and i stands for row that is substracting from
        for (unsigned int i = 0; i < 3; ++i)
        {
            if (i != r)
            {
                double a_ir = mtr_temp._m[i][r];
                for (unsigned int c = 0; c < 3; ++c)
                {
                    mtr_temp._m[i][c] -= a_ir * mtr_temp._m[r][c];
                }
                rhs_temp._v[i] -= a_ir * rhs_temp._v[r];
            }
        }
    }

    // rewritting results
    *x = rhs_temp;

    return true;
}

#endif // GAUSSJORDAN_H
