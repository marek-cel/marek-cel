#ifndef SCENEROOT_H
#define SCENEROOT_H

#include <osg/Group>
#include <osg/Switch>

class SceneRoot
{
public:

    SceneRoot();

    inline osg::Node* getNode() { return _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;
    osg::ref_ptr<osg::Switch> _switch;

    void createScene();
};

#endif // SCENEROOT_H
