#ifndef SIMULATION_H
#define SIMULATION_H

#include <cmath>
#include <iostream>
#include <memory>
#include <fstream>
#include <string>

#include <Vehicle.h>

class Simulation
{
public:

    static constexpr int numVehicles = 2; ///< Number of vehicles in the simulation

    static constexpr int numPosCoord = 3; ///< Number of position coordinates
    static constexpr int numAttCoord = 4; ///< Number of attitude coordinates (quaternion)
    static constexpr int numVelCoord = 3; ///< Number of velocity coordinates
    static constexpr int numAngVelCoord = 3; ///< Number of angular velocity coordinates

    static constexpr int numCoordPerVehicle = numPosCoord + numAttCoord + numVelCoord + numAngVelCoord; ///< Total number of coordinates per vehicle
    static constexpr int numTotalCoord = numVehicles * numCoordPerVehicle; ///< Total number of coordinates in the simulation


    std::ofstream *_of = nullptr; ///< Output file stream

    std::shared_ptr<Vehicle> _tractor;
    std::shared_ptr<Vehicle> _trailer;

    double _state[numTotalCoord]; ///< State vector for the simulation
    double _stateDot[numTotalCoord]; ///< State derivative vector for the simulation

    double _time = 0.0; ///< Current simulation time

    Simulation()
    {
        std::string filename = "output.csv";
        _of = new std::ofstream(filename, std::ios::out | std::ios::trunc);
        if (!_of->is_open())
        {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            exit(1);
        }

        writeHeader();

        initTractor();
        initTrailer();
    }

    ~Simulation()
    {
        if (_of)
        {
            _of->close();
            delete _of;
        }
    }

    void simulate()
    {
        for ( int i = 0; i < 1000; ++i )
        {
            double dt = 0.01; // Time step

            _tractor->update(dt);
            //_trailer->update(dt);

            updateStateVector(_tractor, _state);
            updateStateVector(_trailer, _state + numCoordPerVehicle);
            updateStateDotVector(_tractor, _stateDot);
            updateStateDotVector(_trailer, _stateDot + numCoordPerVehicle);
            integrate(dt);
            (*_of) << _time << ",";
            _time += dt;
            updateVehicle(_tractor, _state);
            updateVehicle(_trailer, _state + numCoordPerVehicle);
            (*_of) << std::endl;
        }
    }

    void writeHeader()
    {
        (*_of) << "t,"
               << "x1,y1,z1,phi1,tht1,psi1,vx1,vy1,vz1,wx1,wy1,wz1,"
               << "x2,y2,z2,phi2,tht2,psi2,vx2,vy2,vz2,wx2,wy2,wz2\n";
        (*_of).flush();
    }

    void initTractor()
    {
        // Mercedes Actros
        _tractor = std::make_shared<Vehicle>();
        _tractor->_mass = 5000.0; // kg
        _tractor->_inertia_BAS._m[0][0] = 10000.0; // kg*m^2
        _tractor->_inertia_BAS._m[1][1] = 10000.0; // kg*m^2
        _tractor->_inertia_BAS._m[2][2] = 10000.0; // kg*m^2
        _tractor->_CD = 0.8; // Coefficient of drag
        _tractor->_referenceArea = 10.0; // m^2
        _tractor->_wheelPos_BAS[0] = Vector3( 2.5, -1.2, 0.5); // Front left wheel position
        _tractor->_wheelPos_BAS[1] = Vector3( 2.5,  1.2, 0.5); // Front right wheel position
        _tractor->_wheelPos_BAS[2] = Vector3(-2.5, -1.2, 0.5); // Rear left wheel position
        _tractor->_wheelPos_BAS[3] = Vector3(-2.5,  1.2, 0.5); // Rear right wheel position
        _tractor->_springCoef = 100'000.0; // N/m
        _tractor->_dampingCoef = 5'000.0; // N*s/m
        _tractor->_wheelRadius = 0.5; // m
        _tractor->_engineTorque = 1000.0; // N*m
        _tractor->_gearRatio = 10.0; // Gear ratio

        _tractor->_position_NED = Vector3(0.0, 0.0, -0.4); // Initial position
        _tractor->_attitude.setRollPitchYaw(RollPitchYaw(0.0, 0.0, 0.0)); // Initial orientation
        _tractor->_velocity_BAS = Vector3(0.0, 0.0, 0.0); // Initial linear velocity
        _tractor->_angularVelocity_BAS = Vector3(0.0, 0.0, 0.0); // Initial angular velocity
    }

    void initTrailer()
    {
        // Schmitz Cargobull
        _trailer = std::make_shared<Vehicle>();
        _trailer->_mass = 10000.0; // kg
        _trailer->_inertia_BAS._m[0][0] = 10000.0; // kg*m^2
        _trailer->_inertia_BAS._m[1][1] = 30000.0; // kg*m^2
        _trailer->_inertia_BAS._m[2][2] = 30000.0; // kg*m^2
        _trailer->_CD = 0.7; // Coefficient of drag
        _trailer->_referenceArea = 8.0; // m^2
        _trailer->_wheelPos_BAS[0] = Vector3(5.0,  -1.2, 0.5); // Front left wheel position
        _trailer->_wheelPos_BAS[1] = Vector3(5.0,   1.2, 0.5); // Front right wheel position
        _trailer->_wheelPos_BAS[2] = Vector3(-5.0, -1.2, 0.5); // Rear left wheel position
        _trailer->_wheelPos_BAS[3] = Vector3(-5.0,  1.2, 0.5); // Rear right wheel position
        _trailer->_springCoef = 120'000.0; // N/m
        _trailer->_dampingCoef = 6'000.0; // N*s/m
        _trailer->_wheelRadius = 0.5; // m

        _trailer->_position_NED = Vector3(-3.0, 0.0, 0.0); // Initial position
        _trailer->_attitude.setRollPitchYaw(RollPitchYaw(0.0, 0.0, 0.0)); // Initial orientation
        _trailer->_velocity_BAS = Vector3(0.0, 0.0, 0.0); // Initial linear velocity
        _trailer->_angularVelocity_BAS = Vector3(0.0, 0.0, 0.0); // Initial angular velocity
    }

    void updateStateVector(std::shared_ptr<Vehicle> vehicle, double* state)
    {
        // Update the state vector with the vehicle's state
        state[0] = vehicle->_position_NED.x();
        state[1] = vehicle->_position_NED.y();
        state[2] = vehicle->_position_NED.z();
        state[3] = vehicle->_attitude._e0;
        state[4] = vehicle->_attitude._ex;
        state[5] = vehicle->_attitude._ey;
        state[6] = vehicle->_attitude._ez;
        state[7] = vehicle->_velocity_BAS.x();
        state[8] = vehicle->_velocity_BAS.y();
        state[9] = vehicle->_velocity_BAS.z();
        state[10] = vehicle->_angularVelocity_BAS.x();
        state[11] = vehicle->_angularVelocity_BAS.y();
        state[12] = vehicle->_angularVelocity_BAS.z();
    }

    void updateStateDotVector(std::shared_ptr<Vehicle> vehicle, double* state)
    {
        // Update the state vector with the vehicle's state
        state[0] = vehicle->_velocity_NED.x();
        state[1] = vehicle->_velocity_NED.y();
        state[2] = vehicle->_velocity_NED.z();
        state[3] = vehicle->_attitude_dot._e0;
        state[4] = vehicle->_attitude_dot._ex;
        state[5] = vehicle->_attitude_dot._ey;
        state[6] = vehicle->_attitude_dot._ez;
        state[7] = vehicle->_acceleration_BAS.x();
        state[8] = vehicle->_acceleration_BAS.y();
        state[9] = vehicle->_acceleration_BAS.z();
        state[10] = vehicle->_angularAcceleration_BAS.x();
        state[11] = vehicle->_angularAcceleration_BAS.y();
        state[12] = vehicle->_angularAcceleration_BAS.z();
    }

    void integrate(double dt)
    {
        // Integrate the state vector
        for (int i = 0; i < numTotalCoord; ++i)
        {
            _state[i] += dt * _stateDot[i];
        }
    }

    void updateVehicle(std::shared_ptr<Vehicle> vehicle, double* state)
    {
        // Update the vehicle's state
        vehicle->_position_NED.x() = state[0];
        vehicle->_position_NED.y() = state[1];
        vehicle->_position_NED.z() = state[2];
        vehicle->_attitude._e0 = state[3];
        vehicle->_attitude._ex = state[4];
        vehicle->_attitude._ey = state[5];
        vehicle->_attitude._ez = state[6];
        vehicle->_velocity_BAS.x() = state[7];
        vehicle->_velocity_BAS.y() = state[8];
        vehicle->_velocity_BAS.z() = state[9];
        vehicle->_angularVelocity_BAS.x() = state[10];
        vehicle->_angularVelocity_BAS.y() = state[11];
        vehicle->_angularVelocity_BAS.z() = state[12];

        // Update the attitude quaternion
        vehicle->_attitude.normalize();

        RollPitchYaw rpy = vehicle->_attitude.getRollPitchYaw();

        // Write the state to the output file
        (*_of) << vehicle->_position_NED.x() << ","
               << vehicle->_position_NED.y() << ","
               << vehicle->_position_NED.z() << ","
               << rpy._phi * 180.0 / M_PI << ","
               << rpy._tht * 180.0 / M_PI << ","
               << rpy._psi * 180.0 / M_PI << ","
               << vehicle->_velocity_BAS.x() << ","
               << vehicle->_velocity_BAS.y() << ","
               << vehicle->_velocity_BAS.z() << ","
               << vehicle->_angularVelocity_BAS.x() << ","
               << vehicle->_angularVelocity_BAS.y() << ","
               << vehicle->_angularVelocity_BAS.z() << ",";
    }
};

#endif // SIMULATION_H
