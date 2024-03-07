#ifndef SCENEROOT_H
#define SCENEROOT_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>
#include <osg/Geode>

#include <osgAnimation/Bone>
#include <osgAnimation/BasicAnimationManager>

////////////////////////////////////////////////////////////////////////////////

class SceneRoot
{
public:

    SceneRoot();

    virtual ~SceneRoot();

    inline osg::Node* getNode() { return _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;

    void CreateScene();

    osg::Geode* createBoneShape(osg::Vec3d vb, osg::Vec3d ve);
};

////////////////////////////////////////////////////////////////////////////////

#endif // SCENEROOT_H
