#ifndef SCENEROOT_H
#define SCENEROOT_H

#include <osg/Group>
#include <osg/Texture2D>

class SceneRoot
{
public:

    SceneRoot();

    inline osg::Node* getNode() { return _root.get(); }

    inline osg::Node* getCenter() { return _center.get(); }

private:

    osg::ref_ptr<osg::Group> _root;
    osg::ref_ptr<osg::Group> _center;

    void createScene();
    void createLight();
    void createBox(osg::Vec3 pos = osg::Vec3());
    void createSphere(osg::Vec3 pos = osg::Vec3());

    std::string readShaderFromFile(const char* path);
    osg::Texture2D* readTextureFromFile(const char* path);
};

#endif // SCENEROOT_H
