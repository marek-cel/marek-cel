#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <vector>

struct Coordinates
{
    double x;   ///< X coordinate
    double y;   ///< Y coordinate
    double z;   ///< Z coordinate
};

class Model
{
public:

    Model(double container_length, double container_width, double container_depth)
        : _container_length(container_length),
          _container_width(container_width),
          _container_depth(container_depth)
    {
        _num_x = 20;
        _num_y = 10;
        _num_z = 10;

        update(0.0);
    }

    void update(double dt)
    {
        _time += dt;
        _coordinates.clear();
        double delta_x = _container_length / _num_x;
        double delta_y = _container_width  / _num_y;
        double delta_z = _container_depth  / _num_z;
        for ( int x = 0; x < _num_x; ++x )
        {
            double max_height = 0.1 * sin(_time + x * 0.2) * _container_depth + 0.8 * _container_depth;
            for ( int y = 0; y < _num_y; ++y )
            {
                for ( int z = 0; z < _num_z; ++z )
                {
                    Coordinates c;
                    c.x = x * delta_x + 0.5 * delta_x;
                    c.y = y * delta_y + 0.5 * delta_y;
                    c.z = static_cast<double>(z) / _num_z * max_height + 0.5 * delta_z;
                    _coordinates.push_back(c);
                }
            }
        }

    }

    std::vector<Coordinates> getCoordinates() const
    {
        return _coordinates;
    }

protected:

    double _time = 0.0; ///< Simulation time

    std::vector<Coordinates> _coordinates;

    double _container_length = 2.0; ///< Height of the container
    double _container_width = 1.0; ///< Width of the container
    double _container_depth = 1.0;  ///< Depth of the container

    int _num_x = 20;
    int _num_y = 10;
    int _num_z = 10;
};

#endif // MODEL_H
