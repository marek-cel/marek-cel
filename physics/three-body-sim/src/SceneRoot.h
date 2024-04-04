#ifndef SCENEROOT_H
#define SCENEROOT_H

#include <osg/Group>

#include <Body.h>

class SceneRoot
{
public:

    float _sunElev_rad = 0.0;
    float _sunAzim_rad = 0.0;

    SceneRoot();

    void update();

    inline osg::Node* getNode() { return _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;

    Body* _bodies[20];

    int _n = 0;

    void createScene();
    void createLight();

    void initSolarSystem();
    void initTwoBodiesSymmetric();
    void initTwoBodiesAsymmetric();
    void initThreeBodiesSymmetric();
    void initThreeBodiesAsymmetric();
    void initThreeBodiesAsymmetric3D();
    void initThreeBodiesAsymmetric3DWithPlanet();
    void initThreeBodiesAsymmetric3DWithPlanetStatic();
};

#endif // SCENEROOT_H
