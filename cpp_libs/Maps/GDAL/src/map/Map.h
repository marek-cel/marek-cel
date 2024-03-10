#ifndef MAP_H
#define MAP_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>

////////////////////////////////////////////////////////////////////////////////

class Layers;
class Satellite;

/**
 * @brief Map scene root class.
 * @see Annex 4 to the Convention on International Civil Aviation - Aeronautical Charts
 */
class Map
{
public:

    static const osg::Vec3 _colorOceans;        ///< color
    static const osg::Vec3 _colorLandmass;      ///< color
    static const osg::Vec3 _colorCoastline;     ///< color
    static const osg::Vec3 _colorWoodland;      ///< color
    static const osg::Vec3 _colorBuiltup;       ///< color
    static const osg::Vec3 _colorWaterInland;   ///< color
    static const osg::Vec3 _colorWaterCourse;   ///< color
    static const osg::Vec3 _colorRoads;         ///< color

    static const double _zOceans;               ///< z-ccordinate
    static const double _zLandmass;             ///< z-ccordinate
    static const double _zWoodland;             ///< z-ccordinate
    static const double _zBuiltup;              ///< z-ccordinate
    static const double _zSatellite;            ///< z-ccordinate
    static const double _zWaterCourse;          ///< z-ccordinate
    static const double _zWaterInland;          ///< z-ccordinate
    static const double _zRoads;                ///< z-ccordinate
    static const double _zCoastline;            ///< z-ccordinate

    /** @brief Constructor. */
    Map();

    /** @brief Destructor. */
    virtual ~Map();

    inline osg::Group* getNode() { return _root.get(); }

    /** */
    void setScale( double scale );

    void setVisibilitySatellite ( bool visible );
    void setVisibilityWoodland  ( bool visible );
    void setVisibilityBuiltup   ( bool visible );
    void setVisibilityInWaters  ( bool visible );
    void setVisibilityRoads     ( bool visible );

private:

    osg::ref_ptr< osg::Group > _root;

    Layers *_layers;        ///< layers
    Satellite *_satellite;
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAP_H
