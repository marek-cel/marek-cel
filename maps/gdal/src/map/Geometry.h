#ifndef GEOMETRY_H
#define GEOMETRY_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief CGI geometry class.
 */
class Geometry
{
public:

    /**
     * @brief Creates quad.
     * @param geom
     * @param v
     * @param texCoords
     * @param alpha
     */
    static void createQuad( osg::Geometry *geom, osg::Vec3Array *v,
                            bool texCoords = false, bool color = false,
                            double alpha = 1.0 );
};

////////////////////////////////////////////////////////////////////////////////

#endif // GEOMETRY_H
