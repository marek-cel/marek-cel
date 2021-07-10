#ifndef MERCATOR_H
#define MERCATOR_H

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Mercator projection coordinates computation class.
 *
 * @see Evenden G.: libproj4: A Comprehensive Library of Cartographic Projection Functions (Preliminary Draft), 2005
 */
class Mercator
{
public:

    static const double _max_x;     ///< [m] maximum Mercator x-coordinate for longitude 180 deg
    static const double _max_y;     ///< [m] maximum Mercator y-coordinate for latitude 85 deg

    /**
     * @brief Computes geodetic latitude.
     * @param y [m] Mercator y-coordinate
     * @param max_error maximum error (solve condition)
     * @param max_iterations maximum number of iterations
     * @return geodetic latitude [rad]
     */
    static double lat( double y, double max_error = 1.0e-9,
                       unsigned int max_iterations = 10 );

    /**
     * @brief Computes geodetic longitude.
     * @param x [m] Mercator x-coordinate
     * @return geodetic longitude [rad]
     */
    static double lon( double x );

    /**
     * @brief Computes Mercator x-coordinate.
     * @param lon [rad] geodetic longitude
     * @return Mercator x-coordinate [m]
     */
    static double x( double lon );

    /**
     * @brief Computes Mercator y-coordinate.
     * @param lat [rad] geodetic latitude
     * @return Mercator y-coordinate [m]
     */
    static double y( double lat );

    /**
     * @brief Computes ellipsoid parallel radius.
     * @param lat_ts [rad] geodetic latitude of true scale
     * @return parallel radius [m]
     */
    static double k0( double lat_ts );

    /**
     * @brief Computes Isometric Latitude kernel.
     * @param lat [rad] geodetic latitude
     * @return Isometric Latitude kernel
     */
    static double t( double lat );

    /**
     * @brief Computes geodetic latitude from the isometric latitude.
     * @param t isometric latitude
     * @param max_error maximum error (solve condition)
     * @param max_iterations maximum number of iterations
     * @return geodetic latitude [rad]
     */
    static double t_inv( double t, double max_error = 1.0e-9,
                         unsigned int max_iterations = 10 );
};

////////////////////////////////////////////////////////////////////////////////

#endif // MERCATOR_H
