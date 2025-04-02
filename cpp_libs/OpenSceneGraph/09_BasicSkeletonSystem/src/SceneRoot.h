#ifndef SCENEROOT_H
#define SCENEROOT_H

#include <osg/Group>
#include <osg/Geode>

#include <osgAnimation/Bone>
#include <osgAnimation/BasicAnimationManager>

class SceneRoot
{
public:

    SceneRoot();

    inline osg::Node* getNode() { return _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;

    void createScene();

    osgAnimation::Bone* createBone(const char* name, const osg::Vec3& trans, osg::Group* parent);
    osgAnimation::Bone* createEndBone(const char* name, const osg::Vec3& trans, osg::Group* parent);

    osgAnimation::Channel* createChannel(const char* name, const osg::Vec3& axis, float rad);

    osg::Geode* createBoneShape(osg::Vec3d vb, osg::Vec3d ve);

    osg::Vec3d getOrthogonal(osg::Vec3d v);

    osg::Vec3d getNormal(osg::Vec3d v0, osg::Vec3d v1, osg::Vec3d v2);
};

#endif // SCENEROOT_H
