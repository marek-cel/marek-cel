#ifndef WGS84_H
#define WGS84_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/CoordinateSystemNode>
#include <osg/PositionAttitudeTransform>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief WGS84 class.
 */
class WGS84
{
public:

    static const double _a;                 ///< [m] equatorial radius
    static const double _b;                 ///< [m] polar radius
    static const double _e2;                ///< [-] ellipsoid first eccentricity squared
    static const double _e;                 ///< [-] ellipsoid first eccentricity

    static const osg::EllipsoidModel _em;   ///<
    static const osg::Quat _enu2ned;        ///<

    /**
     * @brief Returns WGS-84 equatorial radius.
     * @return equatorial radius [m]
     */
    static double getRadiusEquatorial();

    static double getRadiusPolar();

    static osg::Vec3d geo2wgs( double lat, double lon, double alt );

    static void wgs2geo( const osg::Vec3d &r_wgs, double &lat, double &lon, double &alt );

    static osg::Vec3d ned2wgs( const osg::Vec3d &r0_wgs, const osg::Vec3d &v_ned );

    static osg::Vec3d wgs2ned( const osg::Vec3d &r0_wgs, const osg::Vec3d &v_wgs );

    static osg::Vec3d r_ned2wgs( const osg::Vec3d &r0_wgs, const osg::Vec3d &r_ned );

    static osg::Vec3d r_wgs2ned( const osg::Vec3d &r0_wgs, const osg::Vec3d &r_wgs );

    static void setLatLonAltHdg( osg::PositionAttitudeTransform *pat,
                                 double lat, double lon, double alt, double hdg = 0.0 );

    /** @brief Constructor. */
    WGS84();

    /** @brief Constructor. */
    WGS84( double lat, double lon, double alt );

    /** @brief Constructor. */
    WGS84( const osg::Vec3d &position );

    /** @brief Destructor. */
    virtual ~WGS84();

    inline double getLat() const { return _lat; }
    inline double getLon() const { return _lon; }
    inline double getAlt() const { return _alt; }

    inline osg::Quat  getAttitude() const { return _attitude; }
    inline osg::Vec3d getPosition() const { return _position; }

    void set( double lat, double lon, double alt );

    void set( const osg::Vec3d &position );

    inline void setLat( double lat ) { set( lat, _lon, _alt ); }
    inline void setLon( double lon ) { set( _lat, lon, _alt ); }
    inline void setAlt( double alt ) { set( _lat, _lon, alt ); }

private:

    double _lat;
    double _lon;
    double _alt;

    osg::Quat  _attitude;
    osg::Vec3d _position;
};

////////////////////////////////////////////////////////////////////////////////

#endif // WGS84_H
