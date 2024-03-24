#ifndef SKYDOME_H_
#define SKYDOME_H_

#include <osg/Group>
#include <osg/Texture2D>

class SkyDome
{
public:

    float _sunElev_rad = 0.0f;
    float _sunAzim_rad = 0.0f;

    SkyDome();

    void update();

    inline osg::Node* getNode() { return _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;

    osg::ref_ptr<osg::Uniform> _uniformSunElev;

    void createScene();
};

#endif // SKYDOME_H_
