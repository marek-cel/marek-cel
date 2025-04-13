#ifndef VEHICLE_H
#define VEHICLE_H

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

#include <Vector3.h>
#include <Quaternion.h>
#include <Matrix3x3.h>
#include <RollPitchYaw.h>
#include <GaussJordan.h>

double sign(double x)
{
    if (x < 0.0) return -1.0;
    if (x > 0.0) return 1.0;
    return 0.0;
}

/**
 * \brief Vehicle class for simulating vehicle dynamics.
 *
 * Body Axis is defined as follows:
 * - X-axis: forward direction
 * - Y-axis: right direction
 * - Z-axis: down direction
 *
 * Global Axis is defined as follows:
 * - X-axis: North direction
 * - Y-axis: East direction
 * - Z-axis: down direction
 */
class Vehicle
{
public:

    std::ofstream *_of = nullptr; ///< Output file stream


    static constexpr double airDensity = 1.225;         ///< [kg/m^3] air density at sea level
    static constexpr double rollingFriction = 0.05;    ///< rolling friction coefficient
    static constexpr double staticFriction = 0.5;        ///< static friction coefficient
    static constexpr double gravity = 9.81;             ///< [m/s^2] gravitational acceleration
    static constexpr int numWheels = 4;                 ///< number of wheels

    double _mass = 0.0;                 ///< [kg] mass of the body
    Matrix3x3 _inertia_BAS;             ///< [kg*m^2] inertia tensor in Body Axis around the center of mass

    double _CD = 0.0;                   ///< drag coefficient
    double _referenceArea = 0.0;        ///< [m^2] reference area for drag force

    Vector3 _wheelPos_BAS[numWheels];    ///< [m] wheel positions in Body Axis
    double _springCoef = 0.0;           ///< [N/m] spring coefficient
    double _dampingCoef = 0.0;          ///< [N*s/m] damping coefficient
    double _wheelRadius = 0.0;          ///< [m] wheel radius


    Vector3 _position_NED;               ///< [m] vehicle position in Global Axis
    Quaternion _attitude;               ///< quaternion orientation (rotation from Global Axis to Body Axis)
    Quaternion _attitude_inv;           ///< quaternion orientation (rotation from Body Axis to Global Axis)
    RollPitchYaw _attitude_RPY;     ///< roll, pitch, yaw angles in radians
    Vector3 _velocity_BAS;               ///< [m/s] vehicle linear velocity in Body Axis
    Vector3 _velocity_NED;               ///< [m/s] vehicle linear velocity in Global Axis
    Vector3 _angularVelocity_BAS;        ///< [rad/s] angular velocity in Body Axis
    Vector3 _angularVelocity_NED;        ///< [rad/s] angular velocity in Global Axis
    Vector3 _acceleration_BAS;           ///< [m/s^2] linear acceleration in Body Axis
    Vector3 _angularAcceleration_BAS;    ///< [rad/s^2] angular acceleration in Body Axis

    Vector3 _force_BAS;                  ///< [N] force acting on the center of mass in Body Axis
    Vector3 _moment_BAS;                 ///< [N*m] moment acting on the center of mass in Body Axis

    double _engineTorque = 0.0;         ///< [N*m] engine torque
    double _gearRatio = 0.0;           ///< gear ratio

    double _cumulativeTime = 0.0;           ///< [s] cumulative time for simulation

    Vehicle(const char* name)
    {
        std::string filename = name + std::string(".csv");
        _of = new std::ofstream(filename, std::ios::out | std::ios::trunc);
        if (!_of->is_open())
        {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            exit(1);
        }

        writeHeaderToFile();
    }

    ~Vehicle()
    {
        if (_of)
        {
            _of->close();
            delete _of;
        }
    }

    void update(double dt)
    {
        // Update time
        _cumulativeTime += dt;

        // Update forces and moments
        updateForcesAndMoments();

        // Compute accelerations
        computeAcceleration();

        // Integrate to update position and velocity
        integrate(dt);

        // Write data to file
        writeDataToFile();
    }

    void updateForcesAndMoments()
    {
        // Reset forces and moments
        _force_BAS = Vector3(0.0, 0.0, 0.0);
        _moment_BAS = Vector3(0.0, 0.0, 0.0);

        // Gravity force
        Vector3 gravityForce_NED = Vector3(0.0, 0.0, _mass * gravity);
        _force_BAS += _attitude_inv * gravityForce_NED;

        // Drag force
        Vector3 velNormalized = _velocity_BAS.getNormalized();
        double velMagnitude = _velocity_BAS.getLength();
        double dragForce = getDragForce(velMagnitude);
        _force_BAS -= velNormalized * dragForce;

        // Wheel forces and moments
        for ( int i = 0; i < numWheels; ++i )
        {
            updateWheelForcesAndMoments(i);
        }
    }

    void updateWheelForcesAndMoments(int i)
    {
        Vector3 wheelPos_BAS = _wheelPos_BAS[i];
        Vector3 wheelPos_NED = _attitude * wheelPos_BAS + _position_NED;

        double groundHeight = getGroundHeight(wheelPos_NED.x());

        Vector3 contactPoint_NED = Vector3(wheelPos_NED.x(), wheelPos_NED.y(), -groundHeight);
        Vector3 contactPoint_BAS = _attitude_inv * (contactPoint_NED - _position_NED);
        double strutDeflection = wheelPos_BAS.z() - contactPoint_BAS.z();
        if ( strutDeflection > 0 )
        {
            Vector3 wheelForce(0.0, 0.0, 0.0);
            Vector3 wheelMoment(0.0, 0.0, 0.0);

            // Spring force
            double springForce = -_springCoef * strutDeflection;

            // Damping force
            Vector3 contactPointVelocity_BAS = _velocity_BAS + _angularVelocity_BAS % contactPoint_BAS;
            double dampingForce = -_dampingCoef * contactPointVelocity_BAS.z();

            // Rolling resistance
            double rollingResistance = getRollingResistance();

            // Static friction
            double staticFriction = getStaticFriction();

            // Engine wheel force
            double engineWheelForce = getEngineWheelForce();

            // Longitudinal force
            double longitudinalForce = engineWheelForce - rollingResistance * sign(contactPointVelocity_BAS.x());
            longitudinalForce = std::min(longitudinalForce, staticFriction);

            wheelForce.x() = longitudinalForce;
            wheelForce.z() = springForce + dampingForce;


            wheelMoment = contactPoint_BAS % wheelForce;

            _force_BAS += wheelForce;
            _moment_BAS += wheelMoment;
        }
    }

    void computeAcceleration()
    {
        // Compute linear acceleration
        _acceleration_BAS = _force_BAS / _mass;

        // Compute angular acceleration
        if (!solveGaussJordan(_inertia_BAS, _moment_BAS, &_angularAcceleration_BAS))
        {
            std::cerr << "Error: Unable to compute angular acceleration." << std::endl;
            exit(1);
        }
    }

    void integrate(double dt)
    {
        // Update velocity and angular velocity
        _velocity_BAS += _acceleration_BAS * dt;
        _velocity_NED = _attitude * _velocity_BAS;
        _angularVelocity_BAS += _angularAcceleration_BAS * dt;
        _angularVelocity_NED = _attitude * _angularVelocity_BAS;

        // Update position and attitude
        _position_NED += _velocity_NED * dt;
        _attitude = _attitude + _attitude.getDerivative(_angularVelocity_BAS, dt);
        _attitude.setRollPitchYaw(_attitude.getRollPitchYaw());
        _attitude.normalize();
        _attitude_inv = _attitude.getInverse();
        _attitude_RPY = _attitude.getRollPitchYaw();
    }

    double getEngineWheelForce()
    {
        double engineTorqueAfterTransmission = _engineTorque * _gearRatio;
        double torquePerWeel = engineTorqueAfterTransmission / numWheels;
        double wheelForceAtGround = torquePerWeel / _wheelRadius;
        return wheelForceAtGround;
    }

    double getDragForce(double vel)
    {
        return 0.5 * airDensity * _CD * _referenceArea * vel * vel;
    }

    double getRollingResistance()
    {
        return rollingFriction * _mass * gravity;
    }

    double getStaticFriction()
    {
        return staticFriction * _mass * gravity;
    }

    double getGroundHeight(double x_NED)
    {
        double maxHeight = 5.0; // Maximum height of the ground
        double waveLength = 100.0;

        return maxHeight * cos(2.0 * M_PI * x_NED / waveLength) - maxHeight;
    }

    void writeHeaderToFile()
    {
        (*_of) << "Time, "
            << "Position_NED_X, "
            << "Position_NED_Y, "
            << "Position_NED_Z, "
            << "Attitude_RPY_Phi, "
            << "Attitude_RPY_Tht, "
            << "Attitude_RPY_Psi, "
            << "Velocity_BAS_X, "
            << "Velocity_BAS_Y, "
            << "Velocity_BAS_Z, "
            << "AngularVelocity_BAS_X, "
            << "AngularVelocity_BAS_Y, "
            << "AngularVelocity_BAS_Z" << std::endl;

    }

    void writeDataToFile()
    {
        (*_of) << _cumulativeTime << ", "
            << _position_NED.x() << ", "
            << _position_NED.y() << ", "
            << _position_NED.z() << ", "
            << _attitude_RPY._phi * 180.0 / M_PI << ", "
            << _attitude_RPY._tht * 180.0 / M_PI << ", "
            << _attitude_RPY._psi * 180.0 / M_PI << ", "
            << _velocity_BAS.x() << ", "
            << _velocity_BAS.y() << ", "
            << _velocity_BAS.z() << ", "
            << _angularVelocity_BAS.x() << ", "
            << _angularVelocity_BAS.y() << ", "
            << _angularVelocity_BAS.z() << std::endl;
    }

};

#endif // VEHICLE_H
