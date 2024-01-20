#include <map/Satellite.h>

#include <iostream>

#include <osg/Material>
#include <osg/Texture2D>

#include <osgDB/ReadFile>

#include <gdal/gdal_priv.h>

#include <map/Geometry.h>
#include <map/GeoTIFF.h>
#include <map/Map.h>

////////////////////////////////////////////////////////////////////////////////

Satellite::Satellite()
{
    _root = new osg::Group();

    _switch = new osg::Switch();
    _root->addChild( _switch.get() );

    _pat = new osg::PositionAttitudeTransform();
    _switch->addChild( _pat.get() );

    _pat->setPosition( osg::Vec3( 0.0, 0.0, Map::_zSatellite ) );

    readData();
}

////////////////////////////////////////////////////////////////////////////////

Satellite::~Satellite() {}

////////////////////////////////////////////////////////////////////////////////

void Satellite::setVisibility( bool visible )
{
    if ( visible )
        _switch->setAllChildrenOn();
    else
        _switch->setAllChildrenOff();
}

////////////////////////////////////////////////////////////////////////////////

void Satellite::readData()
{
    readData( _pat.get(), "../../../data/oahu_merc.tif" );
    //readData( _pat.get(), "../../../data/world_merc.tif" );
}

////////////////////////////////////////////////////////////////////////////////

void Satellite::readData( osg::Group *parent, const char *file )
{
    // EPSG:3395
    char proj4_merc[] = { "+proj=merc +lon_0=0 +k=1 +x_0=0 +y_0=0 +datum=WGS84 +units=m +no_defs" };

    GeoTIFF geoTiff( file );

    if ( geoTiff.isOpen() )
    {
        if ( geoTiff.compareSpatialRef( proj4_merc ) )
        {
            double x_ul = geoTiff.getMapUpperLeftX();
            double y_ul = geoTiff.getMapUpperLeftY();

            double w = geoTiff.getMapW();
            double h = geoTiff.getMapH();

            osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
            parent->addChild( pat.get() );
            pat->setPosition( osg::Vec3d( x_ul, y_ul, 0.0 ) );

            osg::ref_ptr<osg::Geode> geode = new osg::Geode();
            pat->addChild( geode.get() );

            osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
            geode->addDrawable( geometry.get() );

            osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();

            v->push_back( osg::Vec3( 0.0 ,   h , 0.0 ) );
            v->push_back( osg::Vec3(   w ,   h , 0.0 ) );
            v->push_back( osg::Vec3(   w , 0.0 , 0.0 ) );
            v->push_back( osg::Vec3( 0.0 , 0.0 , 0.0 ) );

            Geometry::createQuad( geometry.get(), v.get(), true );

            osg::ref_ptr<osg::Texture2D> texture;

            osg::ref_ptr<osg::Image> image = osgDB::readImageFile( file );

            if ( image.valid() )
            {
                texture = new osg::Texture2D();
                texture->setImage( image.get() );

                texture->setWrap( osg::Texture2D::WRAP_S, osg::Texture::MIRROR );
                texture->setWrap( osg::Texture2D::WRAP_T, osg::Texture::MIRROR );

                texture->setNumMipmapLevels( 4 );
                texture->setMaxAnisotropy( 1.0f );

                texture->setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_NEAREST );
                texture->setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );

                texture->setUnRefImageDataAfterApply( false );
            }
            else
            {
                std::cerr << "Cannot open image file: " << file << std::endl;
            }

            osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();

            if ( texture.valid() )
            {
                stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
                stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
                stateSet->setTextureAttributeAndModes( 0, texture, osg::StateAttribute::ON );
            }

            // material
            osg::ref_ptr<osg::Material> material = new osg::Material();

            material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
            material->setAmbient( osg::Material::FRONT, osg::Vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );
            material->setDiffuse( osg::Material::FRONT, osg::Vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );

            stateSet->setAttribute( material.get() );
        }
        else
        {
            std::cout << "File: " << file << " projection is NOT EPSG:3395" << std::endl;
        }
    }
    else
    {
        std::cout << "Cannot open dataset: " << file << std::endl;
    }
}
