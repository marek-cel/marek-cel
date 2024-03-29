#include <SceneRoot.h>

#include <iostream>

#include <osg/Geode>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>

#include <osgDB/ReadFile>

#include <QFile>
#include <QTextStream>

#include <utils.h>

SceneRoot::SceneRoot()
{
    _root = new osg::Group();

    _center = new osg::Group();
    _root->addChild(_center.get());

    osg::ref_ptr<osg::StateSet> stateSet = _root->getOrCreateStateSet();

    stateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHTING       , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHT0         , osg::StateAttribute::ON  );
    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );
    stateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DITHER         , osg::StateAttribute::OFF );

    createScene();
}

void SceneRoot::createScene()
{
    createLight();

    _root->addChild(nested.getNode());

    osg::ref_ptr<osg::StateSet> stateSet = _root->getOrCreateStateSet();
    std::string vertCode = readShaderFromFile(":/shaders/shader.vert");
    std::string fragCode = readShaderFromFile(":/shaders/shader.frag");
    //std::cout << "shader.vert:\n" << vertCode;
    //std::cout << "shader.frag:\n" << fragCode;
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode.c_str()));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode.c_str()));
    stateSet->setAttributeAndModes(program.get());
    stateSet->addUniform(new osg::Uniform("texture0", 0));
}

void SceneRoot::createLight()
{
    osg::ref_ptr<osg::PositionAttitudeTransform> lightPat = new osg::PositionAttitudeTransform();
    _root->addChild(lightPat.get());

    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource();
    lightPat->addChild(lightSource.get());

    osg::ref_ptr<osg::Light> lightSun = new osg::Light();

    lightSun->setLightNum(0);

    osg::Vec4 color(1.0, 1.0, 1.0, 1.0);
    osg::Vec3d position(6.0, -2.0, 4.0);

    lightSun->setPosition(osg::Vec4d(position, 1.0));
    lightPat->setPosition(position);

    lightSun->setAmbient  ( color );
    lightSun->setDiffuse  ( color );
    lightSun->setSpecular ( color );

    lightSun->setConstantAttenuation(1.0);

    lightSource->setLight(lightSun.get());

    lightSource->setLocalStateSetModes(osg::StateAttribute::ON);
    lightSource->setStateSetModes(*_root->getOrCreateStateSet(), osg::StateAttribute::ON);
}