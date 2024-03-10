#include <map/Layers.h>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/PositionAttitudeTransform>
#include <osg/Material>

#include <osgDB/ReadFile>

#include <map/Geometry.h>
#include <map/Mercator.h>

#include <map/Map.h>

////////////////////////////////////////////////////////////////////////////////

Layers::Layers()
{
    _root = new osg::Group();

    _switchInWaters  = new osg::Switch();
    _switchWoodland  = new osg::Switch();
    _switchBuiltup   = new osg::Switch();
    _switchRoads     = new osg::Switch();

    _oceans       = new osg::PositionAttitudeTransform();
    _landmass     = new osg::PositionAttitudeTransform();
    _coastline    = new osg::PositionAttitudeTransform();
    _woodland     = new osg::PositionAttitudeTransform();
    _builtup      = new osg::PositionAttitudeTransform();
    _water_course = new osg::PositionAttitudeTransform();
    _water_inland = new osg::PositionAttitudeTransform();
    _roads        = new osg::PositionAttitudeTransform();

    _oceans       ->setPosition( osg::Vec3d( 0.0, 0.0, Map::_zOceans    ) );
    _landmass     ->setPosition( osg::Vec3d( 0.0, 0.0, Map::_zLandmass  ) );
    _coastline    ->setPosition( osg::Vec3d( 0.0, 0.0, Map::_zCoastline ) );
    _woodland     ->setPosition( osg::Vec3d( 0.0, 0.0, Map::_zWoodland  ) );
    _builtup      ->setPosition( osg::Vec3d( 0.0, 0.0, Map::_zBuiltup   ) );
    _roads        ->setPosition( osg::Vec3d( 0.0, 0.0, Map::_zRoads     ) );
    _water_course ->setPosition( osg::Vec3d( 0.0, 0.0, Map::_zWaterCourse ) );
    _water_inland ->setPosition( osg::Vec3d( 0.0, 0.0, Map::_zWaterInland ) );

    _switchWoodland  ->addChild( _woodland     .get() );
    _switchBuiltup   ->addChild( _builtup      .get() );
    _switchInWaters  ->addChild( _water_course .get() );
    _switchInWaters  ->addChild( _water_inland .get() );
    _switchRoads     ->addChild( _roads        .get() );

    _root->addChild( _oceans    .get() );
    _root->addChild( _landmass  .get() );
    _root->addChild( _coastline .get() );

    _root->addChild( _switchWoodland  .get() );
    _root->addChild( _switchBuiltup   .get() );
    _root->addChild( _switchInWaters  .get() );
    _root->addChild( _switchRoads     .get() );

    initLayer( _oceans       .get() , Map::_colorOceans      );
    initLayer( _landmass     .get() , Map::_colorLandmass    );
    initLayer( _coastline    .get() , Map::_colorOceans      );
    initLayer( _woodland     .get() , Map::_colorWoodland    );
    initLayer( _builtup      .get() , Map::_colorBuiltup     );
    initLayer( _roads        .get() , Map::_colorRoads       );
    initLayer( _water_course .get() , Map::_colorWaterCourse );
    initLayer( _water_inland .get() , Map::_colorWaterInland );

    createOcean();
    readLayers();
}

////////////////////////////////////////////////////////////////////////////////

Layers::~Layers() {}

////////////////////////////////////////////////////////////////////////////////

void Layers::setVisibilityWoodland( bool visible )
{
    if ( visible )
        _switchWoodland->setAllChildrenOn();
    else
        _switchWoodland->setAllChildrenOff();
}

////////////////////////////////////////////////////////////////////////////////

void Layers::setVisibilityBuiltup( bool visible )
{
    if ( visible )
        _switchBuiltup->setAllChildrenOn();
    else
        _switchBuiltup->setAllChildrenOff();
}

////////////////////////////////////////////////////////////////////////////////

void Layers::setVisibilityInWaters( bool visible )
{
    if ( visible )
        _switchInWaters->setAllChildrenOn();
    else
        _switchInWaters->setAllChildrenOff();
}

////////////////////////////////////////////////////////////////////////////////

void Layers::setVisibilityRoads( bool visible )
{
    if ( visible )
        _switchRoads->setAllChildrenOn();
    else
        _switchRoads->setAllChildrenOff();
}

////////////////////////////////////////////////////////////////////////////////

void Layers::createOcean()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _oceans->addChild( geode.get() );

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
    geode->addDrawable( geometry.get() );

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();

    v->push_back( osg::Vec3( -Mercator::_max_x, -Mercator::_max_y, 0.0 ) );
    v->push_back( osg::Vec3(  Mercator::_max_x, -Mercator::_max_y, 0.0 ) );
    v->push_back( osg::Vec3(  Mercator::_max_x,  Mercator::_max_y, 0.0 ) );
    v->push_back( osg::Vec3( -Mercator::_max_x,  Mercator::_max_y, 0.0 ) );

    Geometry::createQuad( geometry.get(), v.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Layers::initLayer( osg::Node* layer, osg::Vec3 color, float width )
{
    osg::ref_ptr<osg::Material> material = new osg::Material();
    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    material->setAmbient( osg::Material::FRONT, osg::Vec4( color, 1.0f ) );
    material->setDiffuse( osg::Material::FRONT, osg::Vec4( color, 1.0f ) );
    layer->getOrCreateStateSet()->setAttribute( material.get(),
            osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON );

    osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth();
    lineWidth->setWidth( width );
    layer->getOrCreateStateSet()->setAttributeAndModes( lineWidth.get(),
        osg::StateAttribute::ON );
}

////////////////////////////////////////////////////////////////////////////////

void Layers::readLayers()
{
    readLayer( _landmass     .get() , "../../../data/bnd_polbnd.shp" );
    //readLayer( _coastline    .get() , "../../../data/oahu_coastline.osgb"     );
    //readLayer( _woodland     .get() , "../../../data/oahu_woodland.osgb"      );
    //readLayer( _builtup      .get() , "../../../data/oahu_builtup.osgb"       );
    //readLayer( _roads        .get() , "../../../data/oahu_roads.osgb"         );
    //readLayer( _water_course .get() , "../../../data/oahu_water_course.osgb"  );
    //readLayer( _water_inland .get() , "../../../data/oahu_water_inland.osgb"  );
}

////////////////////////////////////////////////////////////////////////////////

void Layers::readLayer( osg::Group *parent, const char *file )
{
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile( file );

    if ( node.valid() )
    {
        parent->addChild( node.get() );
    }
    else
    {
        std::cerr << "Cannot open file: " << file << std::endl;
    }
}
