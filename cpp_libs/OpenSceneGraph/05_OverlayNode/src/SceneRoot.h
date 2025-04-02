#ifndef SCENEROOT_H
#define SCENEROOT_H

#include <osg/Group>

#include <osgSim/OverlayNode>
#include <osg/PositionAttitudeTransform>

class SceneRoot
{
public:

    SceneRoot();

    inline osg::Node* getNode() { _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;
    osg::ref_ptr<osg::PositionAttitudeTransform> _pat;

    osg::ref_ptr<osgSim::OverlayNode> _overleyNode;

    void createScene();
    void createEarth();
    void createBox();
    void createSquare();
};

#endif // SCENEROOT_H
