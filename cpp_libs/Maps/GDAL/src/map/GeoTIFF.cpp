#include <map/GeoTIFF.h>

////////////////////////////////////////////////////////////////////////////////

GeoTIFF::GeoTIFF() {}

////////////////////////////////////////////////////////////////////////////////

GeoTIFF::GeoTIFF( const char *file )
{
    open( file );
}

////////////////////////////////////////////////////////////////////////////////

GeoTIFF::~GeoTIFF() {}

////////////////////////////////////////////////////////////////////////////////

void GeoTIFF::open( const char *file )
{
    close();

    GDALAllRegister();

    _dataset = static_cast< GDALDataset* >( GDALOpen( file, GA_ReadOnly ) );

    if ( _dataset )
    {
        _dataset->GetGeoTransform( _gt );

        _w_px = _dataset->GetRasterXSize();
        _h_px = _dataset->GetRasterYSize();
    }
}

////////////////////////////////////////////////////////////////////////////////

void GeoTIFF::close()
{
    if ( _dataset )
    {
        GDALClose( _dataset );
    }

    _dataset = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

bool GeoTIFF::compareSpatialRef( const char *proj4 ) const
{
    return ( 0 == strcmp( proj4, getSpatialRefProj4().c_str() ) );
}

////////////////////////////////////////////////////////////////////////////////

bool GeoTIFF::isOpen() const
{
    return ( _dataset != nullptr );
}

////////////////////////////////////////////////////////////////////////////////

std::string GeoTIFF::getSpatialRefProj4() const
{
    std::string result;

    if ( _dataset )
    {
        const OGRSpatialReference *spatialRef = _dataset->GetSpatialRef();

        if ( spatialRef )
        {
            char *proj4 = nullptr;
            spatialRef->exportToProj4( &proj4 );

            if ( proj4 ) result = proj4;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

std::string GeoTIFF::getEPSG() const
{
    std::string result;

    if ( _dataset )
    {
        const OGRSpatialReference *spatialRef = _dataset->GetSpatialRef();

        if ( spatialRef )
        {
            result = spatialRef->GetAttrValue( "PROJCS|GEOGCS|AUTHORITY", 1 );
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

double GeoTIFF::getMapX( double x_px, double y_ln ) const
{
    if ( _dataset )
    {
        return _gt[ 0 ] + x_px * _gt[ 1 ] + y_ln * _gt[ 2 ];
    }

    return std::numeric_limits< double >::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

double GeoTIFF::getMapY( double x_px, double y_ln ) const
{
    if ( _dataset )
    {
        return _gt[ 3 ] + x_px * _gt[ 4 ] + y_ln * _gt[ 5 ];
    }

    return std::numeric_limits< double >::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

double GeoTIFF::getMapUpperLeftX() const
{
    if ( _dataset )
    {
        return _gt[ 0 ];
    }

    return std::numeric_limits< double >::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

double GeoTIFF::getMapUpperLeftY() const
{
    if ( _dataset )
    {
        return _gt[ 3 ];
    }

    return std::numeric_limits< double >::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

double GeoTIFF::getMapW() const
{
    if ( _dataset )
    {
        return _w_px * _gt[ 1 ] + _h_px * _gt[ 2 ];
    }

    return std::numeric_limits< double >::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////

double GeoTIFF::getMapH() const
{
    if ( _dataset )
    {
        return _w_px * _gt[ 4 ] + _h_px * _gt[ 5 ];
    }

    return std::numeric_limits< double >::quiet_NaN();
}
