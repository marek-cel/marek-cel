#ifndef SCENEROOT_H
#define SCENEROOT_H

#include <osg/Group>
#include <osg/PositionAttitudeTransform>

class SceneRoot
{
public:

    SceneRoot();

    inline osg::Node* getNode() { return _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;

    void createScene();
    void createGround();
    void createSceneLight();
};

#endif // SCENEROOT_H
