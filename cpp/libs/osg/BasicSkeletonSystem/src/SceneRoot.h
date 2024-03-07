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

    osg::Geode* createBoneShape( const osg::Vec3& trans,
                                 const osg::Vec4& color );

    osgAnimation::Bone* createBone( const char* name, const osg::Vec3& trans,
                                    osg::Group* parent );

    osgAnimation::Bone* createEndBone( const char* name, const osg::Vec3& trans, osg::Group* parent );

    osgAnimation::Channel* createChannel( const char* name, const osg::Vec3& axis, float rad );
};

////////////////////////////////////////////////////////////////////////////////

#endif // SCENEROOT_H
