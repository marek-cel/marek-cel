
#include <map/Mercator.h>
#include <map/WGS84.h>

////////////////////////////////////////////////////////////////////////////////

const double Mercator::_max_x = Mercator::x( osg::DegreesToRadians( 180.0 ) );
const double Mercator::_max_y = Mercator::y( osg::DegreesToRadians(  85.0 ) );

////////////////////////////////////////////////////////////////////////////////

double Mercator::lat( double y, double max_error, unsigned int max_iterations )
{
    // for lat_ts=0 k0=a
    return t_inv( exp( -y / WGS84::_a ), max_error, max_iterations );
}

////////////////////////////////////////////////////////////////////////////////

double Mercator::lon( double x )
{
    // for lat_ts=0 k0=a
    return x / WGS84::_a;
}

////////////////////////////////////////////////////////////////////////////////

double Mercator::x( double lon )
{
    // for lat_ts=0 k0=a
    return WGS84::_a * lon;
}

////////////////////////////////////////////////////////////////////////////////

double Mercator::y( double lat )
{
    // for lat_ts=0 k0=a
    return WGS84::_a * log( t( lat ) );
}

////////////////////////////////////////////////////////////////////////////////

double Mercator::k0( double lat_ts )
{
    double sinLat = sin( lat_ts );
    return WGS84::_a * cos( lat_ts ) / sqrt( 1.0 - WGS84::_e2 * sinLat*sinLat );
}

////////////////////////////////////////////////////////////////////////////////

double Mercator::t( double lat )
{
    double e_sinLat = WGS84::_e * sin( lat );
    return tan( M_PI_4 + 0.5 * lat ) * pow( ( 1.0 - e_sinLat ) / ( 1.0 + e_sinLat ),
                                            0.5 * WGS84::_e );
}

////////////////////////////////////////////////////////////////////////////////

double Mercator::t_inv( double t, double max_error, unsigned int max_iterations )
{
    double lat = M_PI_2 - 2.0 * atan( t );
    double ex = 0.5 * WGS84::_e;
    double er = 1.0e16;

    unsigned int iteration = 0;

    while ( er > max_error && iteration < max_iterations )
    {
        double e_sinLat = WGS84::_e * sin( lat );
        double lat_new = M_PI_2 - 2.0 * atan( t * pow( ( 1.0 - e_sinLat ) / ( 1.0 + e_sinLat ), ex ) );

        er = fabs( lat_new - lat );
        lat = lat_new;

        iteration++;
    }

    return lat;
}
