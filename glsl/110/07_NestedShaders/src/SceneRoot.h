#ifndef SCENEROOT_H
#define SCENEROOT_H

#include <osg/Group>
#include <osg/Texture2D>

#include <Nested.h>

class SceneRoot
{
public:

    SceneRoot();

    inline osg::Node* getNode() { return _root.get(); }

    inline osg::Node* getCenter() { return _center.get(); }

private:

    osg::ref_ptr<osg::Group> _root;
    osg::ref_ptr<osg::Group> _center;

    Nested nested;

    void createScene();
    void createLight();
};

#endif // SCENEROOT_H
