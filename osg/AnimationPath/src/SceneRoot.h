#ifndef SCENEROOT_H
#define SCENEROOT_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>

#include <osg/MatrixTransform>

////////////////////////////////////////////////////////////////////////////////

class SceneRoot
{
public:

    SceneRoot();

    virtual ~SceneRoot();

    inline osg::Node* getNode() { return _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;

    osg::ref_ptr<osg::MatrixTransform> mt_;

    void CreateWall();
    void CreateDoor();

    void CreateAnimation();
};

////////////////////////////////////////////////////////////////////////////////

#endif // SCENEROOT_H
