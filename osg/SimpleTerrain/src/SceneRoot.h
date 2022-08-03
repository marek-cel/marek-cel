#ifndef SCENEROOT_H
#define SCENEROOT_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>

#include <osgSim/OverlayNode>
#include <osg/PositionAttitudeTransform>

////////////////////////////////////////////////////////////////////////////////

class SceneRoot
{
public:

    SceneRoot();

    virtual ~SceneRoot();

    inline osg::Node* getNode() { m_root.get(); }

private:

    osg::ref_ptr<osg::Group> m_root;
    osg::ref_ptr<osg::PositionAttitudeTransform> m_pat;

    osg::ref_ptr<osgSim::OverlayNode> m_overleyNode;

    void create();

    void createEarth();

    void createBox();

    void createSquare();
};

////////////////////////////////////////////////////////////////////////////////

#endif // SCENEROOT_H
