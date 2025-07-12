#ifndef SPH_H_
#define SPH_H_

#include <cmath>
#include <vector>

/**
 * \brief Particle coordinates structure.
 */
struct ParticleCoordinates
{
    double x;   ///< X coordinate
    double y;   ///< Y coordinate
    double z;   ///< Z coordinate
};

class SPH
{
public:

    SPH(double container_length, double container_width, double container_depth)
        : _container_length(container_length),
          _container_width(container_width),
          _container_depth(container_depth)
    {
        // Initialize the simulation parameters
        _num_particles_x = 20; // Number of particles in X direction
        _num_particles_y = 10; // Number of particles in Y direction
        _num_particles_z = 10; // Number of particles in Z direction

        update(0.0); // Initial update to populate particles
    }

    void update(double dt)
    {
        _time += dt;
        _particles.clear();
        // sample fake wave
        double delta_x = _container_length / _num_particles_x;
        double delta_y = _container_width / _num_particles_y;
        double delta_z = _container_depth / _num_particles_z;
        for ( int x = 0; x < _num_particles_x; ++x )
        {
            double max_height = 0.1 * sin(_time + x * 0.2) * _container_depth + 0.8 * _container_depth;
            for ( int y = 0; y < _num_particles_y; ++y )
            {
                for ( int z = 0; z < _num_particles_z; ++z )
                {
                    ParticleCoordinates particle;
                    particle.x = x * delta_x + 0.5 * delta_x;
                    particle.y = y * delta_y + 0.5 * delta_y;
                    particle.z = static_cast<double>(z) / _num_particles_z * max_height + 0.5 * delta_z;
                    _particles.push_back(particle);
                }
            }
        }

    }

    std::vector<ParticleCoordinates> getParticles() const
    {
        return _particles;
    }

protected:

    double _time = 0.0; ///< Simulation time

    std::vector<ParticleCoordinates> _particles; ///< List of particles

    double _container_length = 2.0; ///< Height of the container
    double _container_width = 1.0; ///< Width of the container
    double _container_depth = 1.0;  ///< Depth of the container

    int _num_particles_x = 20; ///< Number of particles in X direction
    int _num_particles_y = 10; ///< Number of particles in Y direction
    int _num_particles_z = 10; ///< Number of particles in Z direction
};

#endif // SPH_H_
