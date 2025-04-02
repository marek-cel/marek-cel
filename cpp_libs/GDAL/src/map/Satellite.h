#ifndef SATELLITE_H
#define SATELLITE_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/Switch>

////////////////////////////////////////////////////////////////////////////////

class Satellite
{
public:

    /** @brief Constructor. */
    Satellite();

    /** @brief Destructor. */
    virtual ~Satellite();

    inline osg::Group* getNode() { return _root.get(); }

    void setVisibility( bool visible );

private:

    osg::ref_ptr< osg::Group > _root;

    osg::ref_ptr<osg::Switch> _switch;

    osg::ref_ptr<osg::PositionAttitudeTransform> _pat;

    void readData();
    void readData( osg::Group *parent, const char *file );
};

////////////////////////////////////////////////////////////////////////////////

#endif // SATELLITE_H
