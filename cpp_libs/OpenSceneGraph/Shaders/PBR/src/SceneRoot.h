#ifndef SCENEROOT_H
#define SCENEROOT_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>

////////////////////////////////////////////////////////////////////////////////

class SceneRoot
{
public:

    SceneRoot();

    virtual ~SceneRoot();

    inline osg::Node* getNode() { return _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;

    std::string _textureBaseName = "DiamondPlate008C_1K";


    osg::Geode* createSphere( osg::Vec3f origin );

    void createSphere2();
    void createSphere1();

    void attachShader( osg::Geode *geode );
};

////////////////////////////////////////////////////////////////////////////////

#endif // SCENEROOT_H
