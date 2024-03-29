#ifndef NESTED_H
#define NESTED_H

#include <osg/Group>
#include <osg/Texture2D>

class Nested
{
public:

    Nested();

    inline osg::Node* getNode() { return _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;
    osg::ref_ptr<osg::Group> _center;

    void createScene();
    void createBox(osg::Vec3 pos = osg::Vec3());
    void createSphere(osg::Vec3 pos = osg::Vec3());
};

#endif // SCENEROOT_H
