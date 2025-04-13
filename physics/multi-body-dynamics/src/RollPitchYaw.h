#ifndef ROLLPITCHYAW_H
#define ROLLPITCHYAW_H

class RollPitchYaw
{
public:

    double _phi = 0.0;  ///< [rad] angle of rotation about x-axis (roll)
    double _tht = 0.0;  ///< [rad] angle of rotation about y-axis (pitch)
    double _psi = 0.0;  ///< [rad] angle of rotation about z-axis (yaw)

    RollPitchYaw(double phi = 0.0, double tht = 0.0, double psi = 0.0)
    {
        _phi = phi;
        _tht = tht;
        _psi = psi;
    }
};

#endif // ROLLPITCHYAW_H
