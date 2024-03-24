#ifndef SCENEROOT_H
#define SCENEROOT_H

#include <osg/Group>
#include <osg/PositionAttitudeTransform>

#include <SkyDome.h>

class SceneRoot
{
public:

    float _sunElev_rad = 0.0;
    float _sunAzim_rad = 0.0;

    SceneRoot();

    void update();

    inline osg::Node* getNode() { return _root.get(); }

    inline osg::Node* getCenter() { return _center.get(); }

private:

    osg::ref_ptr<osg::Group> _root;
    osg::ref_ptr<osg::Group> _center;

    osg::ref_ptr<osg::PositionAttitudeTransform> _patLight;

    SkyDome _skyDome;

    void createScene();
    void createLight();
    void createPlane();
    void createAxes();
};

#endif // SCENEROOT_H
