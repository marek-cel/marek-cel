#include <Vehicle.h>

void initTractor(Vehicle* tractor);
void initTrailer(Vehicle* trailer);

int main()
{
    std::cout << "Multibody Dynamics Simulation" << std::endl;

    Vehicle Tractor("tractor");
    Vehicle Trailer("trailer");

    initTractor(&Tractor);
    initTrailer(&Trailer);

    for ( int i = 0; i < 1000; ++i )
    {
        double dt = 0.01; // Time step
        Tractor.update(dt);
        Trailer.update(dt);
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
    tractor->_wheelPos_BAS[0] = Vector3( 2.5, -1.2, 0.5); // Front left wheel position
    tractor->_wheelPos_BAS[1] = Vector3( 2.5,  1.2, 0.5); // Front right wheel position
    tractor->_wheelPos_BAS[2] = Vector3(-2.5, -1.2, 0.5); // Rear left wheel position
    tractor->_wheelPos_BAS[3] = Vector3(-2.5,  1.2, 0.5); // Rear right wheel position
    tractor->_springCoef = 100'000.0; // N/m
    tractor->_dampingCoef = 5'000.0; // N*s/m
    tractor->_wheelRadius = 0.5; // m
    tractor->_engineTorque = 1000.0; // N*m
    tractor->_gearRatio = 10.0; // Gear ratio

    tractor->_position_NED = Vector3(0.0, 0.0, -0.4); // Initial position
    tractor->_attitude.setRollPitchYaw(RollPitchYaw(0.0, 0.0, 0.0)); // Initial orientation
    tractor->_velocity_BAS = Vector3(0.0, 0.0, 0.0); // Initial linear velocity
    tractor->_angularVelocity_BAS = Vector3(0.0, 0.0, 0.0); // Initial angular velocity
}

void initTrailer(Vehicle* trailer)
{
    // Schmitz Cargobull
    trailer->_mass = 10000.0; // kg
    trailer->_inertia_BAS._m[0][0] = 10000.0; // kg*m^2
    trailer->_inertia_BAS._m[1][1] = 30000.0; // kg*m^2
    trailer->_inertia_BAS._m[2][2] = 30000.0; // kg*m^2
    trailer->_CD = 0.7; // Coefficient of drag
    trailer->_referenceArea = 8.0; // m^2
    trailer->_wheelPos_BAS[0] = Vector3(5.0,  -1.2, 0.5); // Front left wheel position
    trailer->_wheelPos_BAS[1] = Vector3(5.0,   1.2, 0.5); // Front right wheel position
    trailer->_wheelPos_BAS[2] = Vector3(-5.0, -1.2, 0.5); // Rear left wheel position
    trailer->_wheelPos_BAS[3] = Vector3(-5.0,  1.2, 0.5); // Rear right wheel position
    trailer->_springCoef = 120'000.0; // N/m
    trailer->_dampingCoef = 6'000.0; // N*s/m
    trailer->_wheelRadius = 0.5; // m

    trailer->_position_NED = Vector3(-3.0, 0.0, 0.0); // Initial position
    trailer->_attitude.setRollPitchYaw(RollPitchYaw(0.0, 0.0, 0.0)); // Initial orientation
    trailer->_velocity_BAS = Vector3(0.0, 0.0, 0.0); // Initial linear velocity
    trailer->_angularVelocity_BAS = Vector3(0.0, 0.0, 0.0); // Initial angular velocity
}
