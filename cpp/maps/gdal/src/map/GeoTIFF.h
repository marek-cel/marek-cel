#ifndef GEOTIFF_H
#define GEOTIFF_H

////////////////////////////////////////////////////////////////////////////////

#include <gdal/gdal_priv.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Georefernced TIFF info class.
 */
class GeoTIFF
{
public:

    /** @brief Constructor. */
    GeoTIFF();

    /**
     * @brief Constructor.
     * @param file dataset file name
     */
    GeoTIFF( const char *file );

    /** @brief Destructor. */
    virtual ~GeoTIFF();

    /**
     * @brief Opens dataset.
     * @param file dataset file name
     */
    void open( const char *file );

    /**
     * @brief Closes dataset.
     */
    void close();

    /**
     * @brief Compares spatial refs
     * @param proj4 spatial ref as PROJ.4 string
     * @return returns true if spatial refs are identical, otherwise returns false
     */
    bool compareSpatialRef( const char *proj4 ) const;

    /**
     * @brief Checks if dataset is open.
     * @return returns true if dataset is open, otherwise returns false
     */
    bool isOpen() const;

    /**
     * @brief Gets spatial ref PROJ.4 string.
     * @return spatial ref PROJ.4 string
     */
    std::string getSpatialRefProj4() const;

    /** */
    std::string getEPSG() const;

    /**
     * @brief Returns x coordinate in map units.
     * @param x_px pixel
     * @param y_ln line
     * @return x coordinate in map units
     */
    double getMapX( double x_px, double y_ln ) const;

    /**
     * @brief Returns y coordinate in map units.
     * @param x_px pixel
     * @param y_ln line
     * @return y coordinate in map units
     */
    double getMapY( double x_px, double y_ln ) const;

    /**
     * @brief Returns raster upper left x coordinate in map units.
     * @return raster upper left x coordinate in map units
     */
    double getMapUpperLeftX() const;

    /**
     * @brief Returns raster upper left y coordinate in map units.
     * @return raster upper left y coordinate in map units
     */
    double getMapUpperLeftY() const;

    /**
     * @brief Returns raster width in map units.
     * @return raster width in map units
     */
    double getMapW() const;

    /**
     * @brief Returns raster height in map units.
     * @return raster height in map units
     */
    double getMapH() const;

private:

    GDALDataset *_dataset { nullptr };  ///< dataset

    double _gt[ 6 ] {};                 ///< geo transform

    double _w_px {};                    ///< [px] raster width
    double _h_px {};                    ///< [px] raster height
};

////////////////////////////////////////////////////////////////////////////////

#endif // GEOTIFF_H
