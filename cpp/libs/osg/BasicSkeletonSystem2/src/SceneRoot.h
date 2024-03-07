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

    void createBone(osg::Group* parent);

    osg::Vec3d getOrthogonal(osg::Vec3d v);

    osg::Vec3d getNormal(osg::Vec3d v0, osg::Vec3d v1, osg::Vec3d v2);
};

////////////////////////////////////////////////////////////////////////////////

#endif // SCENEROOT_H
