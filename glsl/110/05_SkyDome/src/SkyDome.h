#ifndef SKYDOME_H_
#define SKYDOME_H_

#include <osg/Group>
#include <osg/Texture2D>
#include <osg/Vec3>

class SkyDome
{
public:

    static const float kSunFaceRadiusNorm;
    static const float kSunGlareRadiusNorm;

    float _sunElev_rad = 0.0f;
    float _sunAzim_rad = 0.0f;

    SkyDome();

    void update();

    inline osg::Node* getNode() { return _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;

    osg::ref_ptr<osg::Uniform> _uniformSunPosNorm;
    osg::ref_ptr<osg::Uniform> _uniformDomeRadius;
    osg::ref_ptr<osg::Uniform> _uniformColorSkyZenith;
    osg::ref_ptr<osg::Uniform> _uniformColorSkyHorizon;
    osg::ref_ptr<osg::Uniform> _uniformColorSun;
    osg::ref_ptr<osg::Uniform> _uniformSunsetCoef;

    osg::Vec3 _sunPosNorm0 = osg::Vec3(0.0, 1.0, 0.0);
    osg::Vec3 _sunPosNorm = _sunPosNorm0;

    osg::Vec3 _colorSkyZenith;
    osg::Vec3 _colorSkyHorizon;
    osg::Vec3 _colorSun;

    float _skyDomeRadius = 10000.0f;

    void createScene();

    int getSkyIndex(float sun_elev_deg);

    void updateColors(float sun_elev_deg);
};

#endif // SKYDOME_H_
