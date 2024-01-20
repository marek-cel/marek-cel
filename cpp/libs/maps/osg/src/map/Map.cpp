#include <map/Map.h>

#include <map/Layers.h>

////////////////////////////////////////////////////////////////////////////////

// ICAO Annex 4 - Aeronautical Charts
const osg::Vec3 Map::_colorOceans      = osg::Vec3( 0.73f, 0.77f, 0.82f );
const osg::Vec3 Map::_colorLandmass    = osg::Vec3( 1.00f, 1.00f, 1.00f );
const osg::Vec3 Map::_colorCoastline   = osg::Vec3( 0.11f, 0.20f, 0.39f );
const osg::Vec3 Map::_colorWoodland    = osg::Vec3( 0.64f, 0.60f, 0.20f );
const osg::Vec3 Map::_colorBuiltup     = osg::Vec3( 0.99f, 0.92f, 0.00f );
const osg::Vec3 Map::_colorWaterCourse = Map::_colorCoastline;
const osg::Vec3 Map::_colorWaterInland = Map::_colorOceans;
const osg::Vec3 Map::_colorRoads       = osg::Vec3( 0.94f, 0.22f, 0.14f );

const double Map::_zOceans      = -20.0;
const double Map::_zLandmass    = -19.0;
const double Map::_zWoodland    = -18.0;
const double Map::_zBuiltup     = -17.0;
const double Map::_zWaterCourse = -15.0;
const double Map::_zWaterInland = -14.0;
const double Map::_zRoads       = -13.0;
const double Map::_zCoastline   = -12.0;

////////////////////////////////////////////////////////////////////////////////

Map::Map() :
    _layers ( nullptr )
{
    _root = new osg::Group();

    osg::ref_ptr<osg::StateSet> stateSet = _root->getOrCreateStateSet();

    stateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHTING       , osg::StateAttribute::OFF );
    stateSet->setMode( GL_LIGHT0         , osg::StateAttribute::OFF );
    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );
    stateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DITHER         , osg::StateAttribute::OFF );
    stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    stateSet->setRenderBinDetails( 0, "RenderBin" );

    _layers = new Layers();

    _root->addChild( _layers->getNode() );
}

////////////////////////////////////////////////////////////////////////////////

Map::~Map()
{
    if ( _layers ) { delete _layers; } _layers = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void Map::setScale( double scale )
{
    //
}

////////////////////////////////////////////////////////////////////////////////

void Map::setVisibilityWoodland( bool visible )
{
    _layers->setVisibilityWoodland( visible );
}

////////////////////////////////////////////////////////////////////////////////

void Map::setVisibilityBuiltup( bool visible )
{
    _layers->setVisibilityBuiltup( visible );
}

////////////////////////////////////////////////////////////////////////////////

void Map::setVisibilityInWaters( bool visible )
{
    _layers->setVisibilityInWaters( visible );
}

////////////////////////////////////////////////////////////////////////////////

void Map::setVisibilityRoads( bool visible )
{
    _layers->setVisibilityRoads( visible );
}
