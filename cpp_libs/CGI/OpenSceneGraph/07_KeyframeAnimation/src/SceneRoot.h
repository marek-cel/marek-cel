#ifndef SCENEROOT_H
#define SCENEROOT_H

#include <osg/Group>
#include <osg/MatrixTransform>

class SceneRoot
{
public:

    SceneRoot();

    inline osg::Node* getNode() { return _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;
    osg::ref_ptr<osg::MatrixTransform> mt_;

    void createScene();
    void createWall();
    void createDoor();
    void createAnimation();
};

#endif // SCENEROOT_H
