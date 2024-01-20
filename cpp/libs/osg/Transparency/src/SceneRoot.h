#ifndef SCENEROOT_H
#define SCENEROOT_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Geometry>
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

    void createBlock( osg::Group *parent );

    void createSprite( osg::Group *parent );

    void createQuad( osg::Geometry *geom, osg::Vec3Array *v,
                     bool texCoords = false, bool color = false,
                     float alpha = 1.0f );
};

////////////////////////////////////////////////////////////////////////////////

#endif // SCENEROOT_H
