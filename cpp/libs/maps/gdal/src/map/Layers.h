#ifndef LAYERS_H
#define LAYERS_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/PositionAttitudeTransform>
#include <osg/Switch>

class Layers
{
public:

    /** @brief Constructor. */
    Layers();

    /** @brief Destructor. */
    virtual ~Layers();

    inline osg::Group* getNode() { return _root.get(); }

    void setVisibilityWoodland  ( bool visible );
    void setVisibilityBuiltup   ( bool visible );
    void setVisibilityInWaters  ( bool visible );
    void setVisibilityRoads     ( bool visible );

private:

    osg::ref_ptr< osg::Group > _root;

    osg::ref_ptr<osg::Switch> _switchWoodland;
    osg::ref_ptr<osg::Switch> _switchBuiltup;
    osg::ref_ptr<osg::Switch> _switchInWaters;
    osg::ref_ptr<osg::Switch> _switchRoads;

    osg::ref_ptr<osg::PositionAttitudeTransform> _oceans;
    osg::ref_ptr<osg::PositionAttitudeTransform> _landmass;
    osg::ref_ptr<osg::PositionAttitudeTransform> _coastline;
    osg::ref_ptr<osg::PositionAttitudeTransform> _woodland;
    osg::ref_ptr<osg::PositionAttitudeTransform> _builtup;
    osg::ref_ptr<osg::PositionAttitudeTransform> _water_course;
    osg::ref_ptr<osg::PositionAttitudeTransform> _water_inland;
    osg::ref_ptr<osg::PositionAttitudeTransform> _roads;

    void createOcean();

    void initLayer( osg::Node* layer, osg::Vec3 color, float width = 1.0f );

    void readLayers();
    void readLayer( osg::Group *parent, const char *file );

};

////////////////////////////////////////////////////////////////////////////////

#endif // LAYERS_H
