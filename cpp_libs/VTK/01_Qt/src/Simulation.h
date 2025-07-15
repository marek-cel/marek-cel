#ifndef SIMULATION_H
#define SIMULATION_H

#include <cmath>
#include <vector>

#include <Container.h>
#include <Particle.h>

class Simulation
{
public:

    Simulation()
    {
        update(0.0); // Initial update to populate particles
    }

    void update(double dt)
    {
        _time += dt;
        _particles.clear();
        // sample fake wave
        double delta_x = Container::length / _num_particles_x;
        double delta_y = Container::width  / _num_particles_y;
        double delta_z = Container::height / _num_particles_z;
        for ( int x = 0; x < _num_particles_x; ++x )
        {
            double max_height = 0.1 * sin(_time + x * 0.2) * Container::height + 0.9 * Container::height;
            for ( int y = 0; y < _num_particles_y; ++y )
            {
                for ( int z = 0; z < _num_particles_z; ++z )
                {
                    Particle particle;
                    particle.x = x * delta_x + 0.5 * delta_x;
                    particle.y = y * delta_y + 0.5 * delta_y;
                    particle.z = static_cast<double>(z) / _num_particles_z * max_height + 0.5 * delta_z;
                    _particles.push_back(particle);
                }
            }
        }

    }

    const std::vector<Particle>& getParticles() const
    {
        return _particles;
    }

protected:

    double _time = 0.0; ///< Simulation time

    std::vector<Particle> _particles; ///< List of particles

    int _num_particles_x = 80; ///< Number of particles in X direction
    int _num_particles_y = 40; ///< Number of particles in Y direction
    int _num_particles_z = 40; ///< Number of particles in Z direction
};

#endif // SIMULATION_H
