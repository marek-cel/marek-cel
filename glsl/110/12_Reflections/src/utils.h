#ifndef UTILS_H
#define UTILS_H

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/SphericalManipulator>

#include <osgDB/ReadFile>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

void setupCameraManipulators(osgViewer::Viewer* viewer, osg::ArgumentParser* arguments);

void setupEventHandlers(osgViewer::Viewer* viewer, osg::ArgumentParser* arguments);

osg::Texture2D* readTextureFromFile(const char* path);

enum class Projection
{
    Azimuthal = 0,  ///< azimuthal projection
    Cylindrical     ///< cylindrical projection
};

void createDome(osg::Geometry* geom, double radius,
                bool texCoords = false, Projection projection = Projection::Cylindrical,
                int lat_segments = 18, int lon_segments = 36);

#endif // UTILS_H
