#include <Vehicle.h>

void initTractor(Vehicle* tractor);

int main()
{
    std::cout << "Multibody Dynamics Simulation" << std::endl;

    Vehicle Tractor("tractor");

    // Initialize tractor parameters
    initTractor(&Tractor);

    for ( int i = 0; i < 1000; ++i )
    {
        Tractor.update(0.01); // Update the vehicle state with a time step of 0.01 seconds
    }

    return 0;
}

void initTractor(Vehicle* tractor)
{
    // Mercedes Actros
    tractor->_mass = 5000.0; // kg
    tractor->_inertia_BAS._m[0][0] = 10000.0; // kg*m^2
    tractor->_inertia_BAS._m[1][1] = 10000.0; // kg*m^2
    tractor->_inertia_BAS._m[2][2] = 10000.0; // kg*m^2
    tractor->_CD = 0.8; // Coefficient of drag
    tractor->_referenceArea = 10.0; // m^2
    tractor->_wheelPos_BAS[0] = Vector3(1.0, -0.5, 0.5); // Front left wheel position
    tractor->_wheelPos_BAS[1] = Vector3(1.0, 0.5, 0.5); // Front right wheel position
    tractor->_wheelPos_BAS[2] = Vector3(-1.0, -0.5, 0.5); // Rear left wheel position
    tractor->_wheelPos_BAS[3] = Vector3(-1.0, 0.5, 0.5); // Rear right wheel position
    tractor->_springCoef = 100000.0; // N/m
    tractor->_dampingCoef = 5000.0; // N*s/m
    tractor->_wheelRadius = 0.5; // m
    tractor->_engineTorque = 1000.0; // N*m
    tractor->_gearRatio = 10.0; // Gear ratio

    tractor->_position_NED = Vector3(0.0, 0.0, -0.5); // Initial position
    tractor->_attitude.setRollPitchYaw(RollPitchYaw(0.0, 0.0, 0.0)); // Initial orientation
    tractor->_velocity_BAS = Vector3(0.0, 0.0, 0.0); // Initial linear velocity
    tractor->_angularVelocity_BAS = Vector3(0.0, 0.0, 0.0); // Initial angular velocity
}
