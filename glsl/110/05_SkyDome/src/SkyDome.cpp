#include <SkyDome.h>

#include <cmath>
#include <iostream>

#include <osg/Geode>
#include <osg/ShapeDrawable>

#include <utils.h>
#include <Colors.h>

#define CGI_SKYDOME_DIAMETER_SUN 0.54

const float SkyDome::kSunFaceRadiusNorm  = tan(osg::DegreesToRadians(CGI_SKYDOME_DIAMETER_SUN  / 2.0));
const float SkyDome::kSunGlareRadiusNorm = tan(osg::DegreesToRadians(10.0));

SkyDome::SkyDome()
{
    _root = new osg::Group();
    createScene();
}

void SkyDome::update()
{
    osg::Quat q(_sunElev_rad, osg::X_AXIS,
               -_sunAzim_rad, osg::Z_AXIS,
                0.0, osg::Y_AXIS);
    _sunPosNorm = q * _sunPosNorm0;

    _uniformSunPosNorm->set(_sunPosNorm);

    float sun_elev_deg = osg::RadiansToDegrees(_sunElev_rad);
    updateColors(sun_elev_deg);
    _uniformColorSkyZenith->set(_colorSkyZenith);
    _uniformColorSkyHorizon->set(_colorSkyHorizon);
    _uniformColorSun->set(_colorSun);
    float sunset_coef = std::max(0.0f, std::min(1.0f, 1.0f - sun_elev_deg / 10.0f));
    _uniformSunsetCoef->set(sunset_coef);

    //std::cout << sunElev_sin << std::endl;
    //std::cout << _sunPos.x() << " " << _sunPos.y() << " " << _sunPos.z() << std::endl;
}

void SkyDome::createScene()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _root->addChild(geode.get());

    osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(osg::Vec3f(), _skyDomeRadius);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(sphere.get());
    //shape->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
    shape->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));
    geode->addDrawable(shape.get());

    osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();

    std::string vertCode = readShaderFromFile(":/shaders/shader.vert");
    std::string fragCode = readShaderFromFile(":/shaders/shader.frag");
    //std::cout << "shader.vert:\n" << vertCode;
    //std::cout << "shader.frag:\n" << fragCode;
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode.c_str()));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode.c_str()));
    stateSet->setAttributeAndModes(program.get());
    _uniformSunPosNorm = new osg::Uniform("sun_pos_norm", _sunPosNorm);
    _uniformDomeRadius = new osg::Uniform("dome_radius", _skyDomeRadius);
    _uniformColorSkyZenith  = new osg::Uniform("color_sky_zenith"  , Colors::sky[8]);
    _uniformColorSkyHorizon = new osg::Uniform("color_sky_horizon" , Colors::fog[8]);
    _uniformColorSun = new osg::Uniform("color_sun" , Colors::sun[8]);
    _uniformSunsetCoef = new osg::Uniform("sunset_coef" , 0.0f);
    stateSet->addUniform(new osg::Uniform("sun_face_radius_norm", kSunFaceRadiusNorm));
    stateSet->addUniform(new osg::Uniform("sun_glare_radius_norm", kSunGlareRadiusNorm));
    stateSet->addUniform(_uniformSunPosNorm.get());
    stateSet->addUniform(_uniformDomeRadius.get());
    stateSet->addUniform(_uniformColorSkyZenith.get());
    stateSet->addUniform(_uniformColorSkyHorizon.get());
    stateSet->addUniform(_uniformColorSun.get());
    stateSet->addUniform(_uniformSunsetCoef.get());
}

int SkyDome::getSkyIndex(float sun_elev_deg)
{
    int sky_num = 0;
    if ( sun_elev_deg >= -10.0f )
    {
        if ( sun_elev_deg < 10.0f )
        {
            sky_num = floor(8 * (sun_elev_deg + 10.0f) / 20.0f + 0.5f);
            sky_num = std::min(std::max(sky_num, 0), 8);
        }
        else
        {
            sky_num = 8;
        }
    }
    return sky_num;
}

void SkyDome::updateColors(float sun_elev_deg)
{
    _colorSkyZenith = Colors::sky[0];
    _colorSkyHorizon = Colors::haze[0];
    _colorSun = Colors::sun[0];

    if ( sun_elev_deg >= -10.0f )
    {
        if ( sun_elev_deg < 10.0f )
        {
            int sky_num = floor(8 * (sun_elev_deg + 10.0f) / 20.0f);
            sky_num = std::min(std::max(sky_num, 0), 8);
            float elev_num = sky_num * 2.5f - 10.0f;
            //std::cout << sky_num << " " << elev_num << " " << sun_elev_deg << std::endl;
            float coef = (sun_elev_deg - elev_num) / 2.5;
            _colorSkyZenith = Colors::sky[sky_num] * (1.0 - coef) + Colors::sky[sky_num+1] * coef;
            _colorSkyHorizon = Colors::haze[sky_num] * (1.0 - coef) + Colors::haze[sky_num+1] * coef; //Colors::haze[sky_num];

            if ( sun_elev_deg > 0.0f )
            {
                int sun_num = floor(10.0f * (sun_elev_deg) / 10.0f);
                float elev_num = sun_num;
                float coef = (sun_elev_deg - elev_num) / 1.0;
                _colorSun = Colors::sun[sun_num] * (1.0 - coef) + Colors::sun[sun_num+1] * coef;
            }
        }
        else
        {
            _colorSkyZenith = Colors::sky[8];
            _colorSkyHorizon = Colors::haze[8];
            _colorSun = Colors::sun[10];
        }
    }
}
